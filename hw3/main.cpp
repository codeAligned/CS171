#include <iostream>
#include <list>
#include <vector>
#include <cassert>
#include <limits>
#include <cmath>
#include <stdlib.h>
#include "data.h"
#include "matrix.h"
#include "raster.h"
#include "vec3.h"

using namespace std;
vector <Light> gLights;
CameraBlock gCamera;
Material gMaterial;
Image *gImage;
int gShadingMode;
vector<Block> &parse_test(istream &datafile);

Vec3 lightingFunction(Vec3 vertex, Vec3 normal, 
                      Material material, 
                      vector <Light> lights, CameraBlock camera) 
{
    //std::cout << "V: " << vertex.x << " " << vertex.y << " " << vertex.z << std::endl;
    //std::cout << "N: " << normal.x << " " << normal.y << " " << normal.z << std::endl;

    Vec3 scolor(material.specular.x, material.specular.y, material.specular.z);
    Vec3 dcolor(material.diffuse.x, material.diffuse.y, material.diffuse.z);
    Vec3 ambient(material.ambient.x, material.ambient.y, material.ambient.z);
    double shiny = material.shininess;

    Vec3 diffuse(0, 0, 0); // start off diffuse at 0
    Vec3 specular(0, 0, 0); // start off specular at 0

    Vec3 cameraPosition(camera.position.x,
                        camera.position.y,
                        camera.position.z);

    for (int i = 0; i < lights.size(); i++) {
        Light light = lights[i];
        Vec3 lc(light.color.x, light.color.y, light.color.z);

        Vec3 lx(light.location.x, light.location.y, light.location.z);

        Vec3 vertexToLight = lx - vertex;
        vertexToLight.normalize(); // make this a unit vector

        double normalDotVtoL = normal.dot(vertexToLight);
        Vec3 diffuseAddition = lc;
        // diffuseAddition = lc * (normal . unit(lx - vertex)
        diffuseAddition.multiply(normalDotVtoL);
        diffuseAddition.zeroClip();
        //std::cout << "DDIFFUSE:" << diffuseAddition.x << " " << diffuseAddition.y <<  " " << diffuseAddition.z << std::endl;

        diffuse += diffuseAddition;

        Vec3 cameraToLight = cameraPosition - vertex;
        cameraToLight.normalize(); // make this a unit vector

        Vec3 addPositions = cameraToLight + vertexToLight;
        addPositions.normalize();

        double k = normal.dot(addPositions);
        if (k < 0.0) { // zeroclip k
            k = 0.0;
        }

        double exponent = pow(k, shiny);  // k ^ shiny

        Vec3 specularAddition = lc;
        specularAddition.multiply(exponent);
        specularAddition.zeroClip();

        specular += specularAddition;
        //std::cout << "SPECULAR:" << specularAddition.x << " " << specularAddition.y <<  " " << specularAddition.z << std::endl;
    }

    diffuse.oneClip();  // clamp diffuse values to 1
    //std::cout << "D: " << diffuse.x << " " << diffuse.y << " " << diffuse.z << std::endl;

    Vec3 diffuseTerm(diffuse.x * dcolor.x,
                     diffuse.y * dcolor.y,
                     diffuse.z * dcolor.z);
    Vec3 specularTerm(specular.x * scolor.x,
                      specular.y * scolor.y,
                      specular.z * scolor.z);
    //std::cout << "S: " << specularTerm.x << " " << specularTerm.y << " " << specularTerm.z << std::endl;
    Vec3 RGB = ambient + diffuseTerm + specularTerm;
    RGB.oneClip();
    //std::cout << RGB.x << " " << RGB.y << " " << RGB.z << std::endl;
    return RGB;
}

// makes the pixel at (x,y) on the canvas the color in RasterParam
void drawPixel(int x, int y, double a, double b, double g, void *data) {

    RasterParam *param = (RasterParam *)(data);
    assert (param != NULL);
    assert (param->image != NULL);
    assert (x >= 0 && x < param->image->width);
    assert (y >= 0 && y < param->image->height);

    double z = (a * param->p1NDC.z) + (b * param->p2NDC.z) + (g * param->p3NDC.z);
    if (z >= -1.0 && z <= 1.0 && z < param->image->zBuffer[param->image->height - 1 - y][x]) {
        Pixel color;
        if (param->shadingMode == 0) {
            color = param->polygonColor;
        } else if (param->shadingMode == 1) { // for Gouraud, do some interpolation of colors
            double rgbR = (a * param->p1Color.x) + 
                          (b * param->p2Color.x) + 
                          (g * param->p3Color.x);
            double rgbG = (a * param->p1Color.y) + 
                          (b * param->p2Color.y) + 
                          (g * param->p3Color.y);
            double rgbB = (a * param->p1Color.z) + 
                          (b * param->p2Color.z) + 
                          (g * param->p3Color.z);

            color.r = (int)(rgbR * 255);
            color.g = (int)(rgbG * 255);
            color.b = (int)(rgbB * 255);
        } else if (param->shadingMode == 2) {

            // linearly interpolated normals in world space
            double normX = (a * param->p1Norm.x) + 
                           (b * param->p2Norm.x) + 
                           (g * param->p3Norm.x);
            double normY = (a * param->p1Norm.y) + 
                           (b * param->p2Norm.y) + 
                           (g * param->p3Norm.y);
            double normZ = (a * param->p1Norm.z) + 
                           (b * param->p2Norm.z) + 
                           (g * param->p3Norm.z);
            Vec3 normInterpolated(normX, normY, normZ);
            normInterpolated.normalize();

            double pointX = (a * param->p1World.x) + 
                            (b * param->p2World.x) + 
                            (g * param->p3World.x);
            double pointY = (a * param->p1World.y) + 
                            (b * param->p2World.y) + 
                            (g * param->p3World.y);
            double pointZ = (a * param->p1World.z) + 
                            (b * param->p2World.z) + 
                            (g * param->p3World.z);
            Vec3 pointInterpolated(pointX, pointY, pointZ);

            Vec3 rgb = lightingFunction(pointInterpolated, normInterpolated, gMaterial, gLights, gCamera);

            color.r = (int)(rgb.x * 255);
            color.g = (int)(rgb.y * 255);
            color.b = (int)(rgb.z * 255);
        }
        param->image->canvas[param->image->height - 1 - y][x] = color;
        param->image->zBuffer[param->image->height - 1 - y][x] = z;
    }

    //std::cerr << "drawPixel X: " << x << " Y: " << y << " " << param->color.r << " " << param->color.g << " " << param->color.b << std::endl;
    //param->image->canvas[param->image->height - 1 - y][x] = param->color;
}


// print image to stdout in ppm format
void printImage(Image *image) {
    assert(image != NULL);

    /* Output some header info for the PPM file */
    std::cout << "P3" << std::endl;
    std::cout << image->width << " " << image->height << std::endl;
    std::cout << "255" << std::endl;
    std::cout << " " << std::endl;

    for (int i = 0; i < image->height; ++i) {
        for (int j = 0; j < image->width; ++j) {
            std::cout << image->canvas[i][j].r << " " << image->canvas[i][j].g << " " << image->canvas[i][j].b << std::endl;
        }
    } 
}

// initialize image to black, and zbuffer to max
void initImage(Image *image) {

    assert(image != NULL);
    assert(image->canvas != NULL);
    assert(image->zBuffer != NULL);

    // Zero out all pixels on the canvas
    Pixel black;
    black.r = black.g = black.b = 0;
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            image->canvas[i][j] = black;
        }
    }
    
    // initialize zBuffer
    for (int i = 0; i < image->height; i++) {
        for (int j = 0; j < image->width; j++) {
            image->zBuffer[i][j] = numeric_limits<double>::max();
        }
    }

    /*
    for (int i = 0; i < yRes; i++) {
        for (int j = 0; j < xRes; j++) {
            std::cerr << "I: " << i << " J: " << j << "  "
                      <<  image->zBuffer[i][j] << std::endl;
        }
    }
    */
}

// allocate memory for image
Image *allocImage(int xRes, int yRes) {
    Image *image = (Image *) malloc(sizeof(Image));
    assert(image != NULL);
    image->width = xRes;
    image->height = yRes;
    image->canvas = (Pixel**) malloc(image->height * (sizeof(Pixel*)));
    for (int i = 0; i < image->width; i++) {
        image->canvas[i] = (Pixel*) malloc(image->width * (sizeof(Pixel)));
    }

    image->zBuffer = (double **) malloc(yRes * (sizeof(double*)));
    for (int i = 0; i < xRes; i++) {
        image->zBuffer[i] = (double*) malloc(xRes * (sizeof(double)));
    }
    return image;
}

// deallocate memory for image
void deallocImage(Image *image) {
    assert(image != NULL);
    for (int i = 0; i < image->width; i++) {
        free(image->canvas[i]);
    }
    free(image->canvas);
    free(image);
}

/* given a value of the endpont of a line on a scale from min to max, 
map it to the pixel of the image of size resolution */
int getPixel(double value, double min, double max, int resolution) {

    float valuePerPixel = (value - min) / (max - min);

    /* note that we really want to map from 0 to (resolution - 1), which
    is the maximum size of our array */
    float pixel = valuePerPixel * (resolution - 1);
    return pixel;
}

int ndcToWin(double value, int resolution) {
    // in NDC everything between -1 and 1
    return getPixel(value, -1, 1, resolution);
}

void drawFace(int point1Idx, int point2Idx, int point3Idx,
              int normal1Idx, int normal2Idx, int normal3Idx,
              int xRes, int yRes, 
              vector<Vec3> &pointsTransformed,
              vector<Vec3> &pointsWorldSpace,
              vector<Vec3> &newNormals)
{
    assert(pointsTransformed.size() == pointsWorldSpace.size());
    assert(point1Idx >= 0 && point1Idx < pointsTransformed.size());
    assert(point2Idx >= 0 && point2Idx < pointsTransformed.size());
    assert(point3Idx >= 0 && point3Idx < pointsTransformed.size());
    assert(normal1Idx >= 0 && normal1Idx < newNormals.size());
    assert(normal2Idx >= 0 && normal2Idx < newNormals.size());
    assert(normal3Idx >= 0 && normal3Idx < newNormals.size());
    
    // grab points in NDC for Backface Culling
    Vec3 p1NDC = pointsTransformed[point1Idx];
    Vec3 p2NDC = pointsTransformed[point2Idx];
    Vec3 p3NDC = pointsTransformed[point3Idx];

    Vec3 P3subP2 = p3NDC - p2NDC;
    Vec3 P1subP2 = p1NDC - p2NDC;
    // find n = (p3 - p2) x (p1 - p2)
    Vec3 crossVec3 = P3subP2.cross(P1subP2);
    if (crossVec3.z <= 0.0) {
        return; // if the z component is negative, don't draw polygon
    }
    // Finished Backface culling.  If we reached here, the z component is 
    // positive and we will draw the polygon.

    //std::cerr << "DRAWING THE POLYGON" << std::endl;
    //std::cerr <<  "POINTS: "<< point1Idx << point2Idx << point3Idx << std::endl;
    //std::cerr <<  "NORMS: "<< normal1Idx << normal2Idx << normal3Idx << std::endl;

    Vec3 p1 = pointsWorldSpace[point1Idx];
    Vec3 p2 = pointsWorldSpace[point2Idx];
    Vec3 p3 = pointsWorldSpace[point3Idx];
    //std::cerr << "Point1: ";
    //p1.print();
    //std::cerr << "Point2: ";
    //p2.print();
    //std::cerr << "Point3: ";
    //p3.print();

    Vec3 n1 = newNormals[normal1Idx];
    Vec3 n2 = newNormals[normal2Idx];
    Vec3 n3 = newNormals[normal3Idx];

    // needed by all shading modes
    RasterParam rasterParam;
    rasterParam.image = gImage;
    rasterParam.shadingMode = gShadingMode;
    rasterParam.p1NDC = p1NDC;
    rasterParam.p2NDC = p2NDC;
    rasterParam.p3NDC = p3NDC;

    if (gShadingMode == 0) {
        // for Flat lighting, we will avg the points and normals
        double x_avg = (p1.x + p2.x + p3.x) / 3;
        double y_avg = (p1.y + p2.y + p3.y) / 3;
        double z_avg = (p1.z + p2.z + p3.z) / 3;
        Vec3 avgPoint(x_avg, y_avg, z_avg);

        double n_x_avg = (n1.x + n2.x + n3.x) / 3;
        double n_y_avg = (n1.y + n2.y + n3.y) / 3;
        double n_z_avg = (n1.z + n2.z + n3.z) / 3;
        Vec3 avgNorm(n_x_avg, n_y_avg, n_z_avg);

        //std::cout << "P1: " << p1.x << " " << p1.y << " " << p1.z << std::endl;
        //std::cout << "P2: " << p2.x << " " << p2.y << " " << p2.z << std::endl;
        //std::cout << "P3: " << p3.x << " " << p3.y << " " << p3.z << std::endl;


        Vec3 rgb = lightingFunction(avgPoint, avgNorm, gMaterial, gLights, gCamera);
        //Vec3 rgb = lightingFunction(p1, n1, gMaterial, gLights, gCamera);
        //Vec3 rgb1 = lightingFunction(p2, n2, gMaterial, gLights, gCamera);
        //Vec3 rgb2 = lightingFunction(p3, n3, gMaterial, gLights, gCamera);
        Pixel polygonColor;

        polygonColor.r = (int)(rgb.x * 255);
        polygonColor.g = (int)(rgb.y * 255);
        polygonColor.b = (int)(rgb.z * 255);

        rasterParam.polygonColor = polygonColor;

    } else if (gShadingMode == 1) {
        Vec3 rgb1 = lightingFunction(p1, n1, gMaterial, gLights, gCamera);
        Vec3 rgb2 = lightingFunction(p2, n2, gMaterial, gLights, gCamera);
        Vec3 rgb3 = lightingFunction(p3, n3, gMaterial, gLights, gCamera);

        rasterParam.p1Color = rgb1;
        rasterParam.p2Color = rgb2;
        rasterParam.p3Color = rgb3;
    } else if (gShadingMode == 2) {
        rasterParam.p1World = p1;
        rasterParam.p2World = p2;
        rasterParam.p3World = p3;

        rasterParam.p1Norm = n1;
        rasterParam.p2Norm = n2;
        rasterParam.p3Norm = n3;
    }

    DrawTriangle(ndcToWin(p1NDC.x, xRes), 
                 ndcToWin(p1NDC.y, yRes),
                 ndcToWin(p2NDC.x, xRes),
                 ndcToWin(p2NDC.y, yRes),
                 ndcToWin(p3NDC.x, xRes),
                 ndcToWin(p3NDC.y, yRes),
                 xRes,
                 yRes,
                 &drawPixel,
                 (void *)(&rasterParam));
}

int main(int argc, char* argv[])
{
    if (argc != 4) {
        std::cerr << "USAGE: shaded n [xRes] [yRes]" << std::endl;
        std::cerr << "(n is which shading mode to use: 0 = Flat, 1 = Gouraud, 2 = Phong)" << std::endl;
        exit(1);
    }

    gShadingMode = atoi(argv[1]);
    int xRes = atoi(argv[2]);
    int yRes = atoi(argv[3]);

    assert(xRes >= 0);
    assert(yRes >= 0);

    gImage = allocImage(xRes, yRes);  // setup image
    initImage(gImage);

    vector<Block> &blocks = parse_test(cin);

    Matrix Camera = Matrix(4,4);
    Matrix CameraInverse = Matrix(4,4);
    Matrix Perspective = Matrix(4,4);


    for (size_t i = 0; i < blocks.size(); i++) {
        Block block = blocks[i];
        if (block.blockType == 0) {

            gCamera = block.camera;

            Matrix T = Matrix(4,4);
            T.translationMatrix(block.camera.position.x, block.camera.position.y, block.camera.position.z);

            Matrix R = Matrix(4,4);
            R.rotationMatrix(block.camera.orientation.x, block.camera.orientation.y, block.camera.orientation.z, block.camera.orientation.w);

            Camera *= T;
            Camera *= R;

            CameraInverse = Camera;
            CameraInverse = CameraInverse.invert();

            // construct Persepctive Matrix from other info
            double n = block.camera.nearDistance;
            double f = block.camera.farDistance;
            double l = block.camera.left;
            double r = block.camera.right;
            double t = block.camera.top;
            double b = block.camera.bottom;
            assert (r != l);
            assert (t != b);
            assert (n != f);
            Perspective(1,1) = 2 * n / (r - l);
            Perspective(2,2) = 2 * n / (t - b);
            Perspective(3,3) = -(f + n) / (f - n);
            Perspective(4,4) = 0;
            Perspective(1,3) = (r + l) / (r - l);
            Perspective(2,3) = (t + b) / (t - b);
            Perspective(3,4) = (-2 * f * n) / (f - n);
            Perspective(4,3) = -1;

        } else if (block.blockType == 1) {
            SeparatorBlock separator = block.separator;
            vector <Transform> transforms = separator.transforms;
            vector <Coordinate3> points = separator.points;
            vector <IndexedFaceSet> indices = separator.indices;
            Material material = separator.material;
            gMaterial = material;


            // grab out normal indices
            vector <double> normalIndices = separator.normalIndices;

            // we will multiple the result of every Transform block to get
            // the final transform
            Matrix finalTransformResult = Matrix(4,4);  // start with identity 4x4
            Matrix finalNormalTransform = Matrix(4,4);

            for (size_t i = 0; i < transforms.size(); i++) { // loop through Transform blocks

                Matrix transformResult = Matrix(4,4);  // start with identity 4x4
                Matrix normalTransform = Matrix(4,4);
                Matrix normalTransformInverse = Matrix(4,4);
                Matrix normalTransformInverseTranpose = Matrix(4,4);

                Matrix translation = Matrix(4,4);
                Matrix rotation = Matrix(4,4);
                Matrix scaleFactor = Matrix(4,4);

                Transform transform = transforms[i];
                vector <TransformCommand> transformations = transform.transformations;
                // loop through each command in a single transform block
                for (size_t j = 0; j < transformations.size(); j++) {
                    TransformCommand transformCommand = transformations[j];
                    string type = transformCommand.transformation;
                    vector<double> args = transformCommand.data;
                    if (type == "T") {
                        Matrix T = Matrix(4,4);
                        T.translationMatrix(args[0], args[1], args[2]);
                        //std::cerr << "T=" << std::endl;
                        //T.print();
                        translation = T;
                    } else if (type == "R") {
                        Matrix R = Matrix(4,4);
                        R.rotationMatrix(args[0], args[1], args[2], args[3]);
                        //std::cerr << "R=" << std::endl;
                        //R.print();
                        rotation = R;
                    } else if (type == "S") {
                        Matrix S = Matrix(4,4);
                        S.scaleFactorMatrix(args[0], args[1], args[2]);
                        //std::cerr << "S=" << std::endl;
                        //S.print();
                        scaleFactor = S;
                    }
                }
                // multiple in correct order: S = TRS
                transformResult *= translation;
                transformResult *= rotation;
                transformResult *= scaleFactor;

                // multiple the final transform by the result of this transform block
                finalTransformResult *= transformResult;

                // we will transform normals by:
                // N_new = Transpose(Inverse(R*S)) * N
                normalTransform *= rotation;
                normalTransform *= scaleFactor;
                finalNormalTransform *= normalTransform;
            }

            Matrix finalNormalInverse = finalNormalTransform.invert();

            // finalNormalInverseTranpose = Tranpose(Inverse(R*S))
            // we will apply this transformation to each normal to transform to world space
            Matrix finalNormalInverseTranspose = finalNormalInverse.transpose();

            vector <Vec3> newNormals;  // normals transformed to world space!

            vector <Vector3> normals = separator.normals;
            for (size_t i = 0; i < normals.size(); i++) {
                Vector3 norm = normals[i];
                //std::cerr << "NORMAL: " << norm.x << " " << norm.y << " " << norm.z << std::endl;
                Matrix Normal = Matrix(4,1);
                Normal(1,1) = norm.x;
                Normal(2,1) = norm.y;
                Normal(3,1) = norm.z;
                Normal(4,1) = 1; // homogenize by making w = 1
                Matrix transformedNormal = finalNormalInverseTranspose * Normal;
                double x = transformedNormal(1,1);
                double y = transformedNormal(2,1);
                double z = transformedNormal(3,1);
                double w = transformedNormal(4,1);
                //transformedNormal.print();
                x /= w; // normalize by dividing by w'
                y /= w;
                z /= w;
                Matrix Homogenized = Matrix(3,1);
                Homogenized(1,1) = x;
                Homogenized(2,1) = y;
                Homogenized(3,1) = z;
                //Homogenized.print();
                Homogenized.normalize();  // extra check to normalized normal
                Vec3 newNorm(Homogenized(1,1),
                             Homogenized(2,1),
                             Homogenized(3,1));
                newNormals.push_back(newNorm);
            }


            vector <Vec3> pointsTransformed; // into NDC
            Matrix PCO = Matrix(4,4);
            PCO *= Perspective;
            PCO *= CameraInverse;
            PCO *= finalTransformResult;
            // grab the Coordinate3 points, and transform them to x,y pixels
            for (size_t i = 0; i < points.size(); i++) {
                vector <Vector3> vectorOfPoints = points[i].points;
                for (size_t j = 0; j < vectorOfPoints.size(); j++) {
                    Vector3 vect = vectorOfPoints[j];
                    Matrix Point = Matrix(4,1);
                    Point(1,1) = vect.x;
                    Point(2,1) = vect.y;
                    Point(3,1) = vect.z;
                    Point(4,1) = 1; // homogenize by making w = 1
                    Matrix transformedPoint = PCO * Point;
                    double x = transformedPoint(1,1);
                    double y = transformedPoint(2,1);
                    double z = transformedPoint(3,1);
                    double w = transformedPoint(4,1);
                    x /= w; // normalize by dividing by w'
                    y /= w; 
                    z /= w;
                    Vec3 p(x, y, z);
                    pointsTransformed.push_back(p);
                    //std::cerr << "POINTS TRANSFORMED!!: " << x << " " << y << " " << z << std::endl;
                }
            }

            // transform by only Transform blocks, to get Points transformed to World Space
            vector <Vec3> pointsWorldSpace;
            for (size_t i = 0; i < points.size(); i++) {
                vector <Vector3> vectorOfPoints = points[i].points;
                for (size_t j = 0; j < vectorOfPoints.size(); j++) {
                    Vector3 vect = vectorOfPoints[j];
                    Matrix Point = Matrix(4,1);
                    Point(1,1) = vect.x;
                    Point(2,1) = vect.y;
                    Point(3,1) = vect.z;
                    Point(4,1) = 1; // homogenize by making w = 1
                    Matrix transformedPoint = finalTransformResult * Point;
                    //finalTransformResult.print();
                    double x = transformedPoint(1,1);
                    double y = transformedPoint(2,1);
                    double z = transformedPoint(3,1);
                    double w = transformedPoint(4,1);
                    x /= w; // normalize by dividing by w'
                    y /= w; 
                    z /= w;
                    Vec3 p(x, y, z);
                    pointsWorldSpace.push_back(p);
                    //std::cerr << "POINTS WORLD SPACE; " << x << y << z << std::endl;
                }
            }


            typedef vector <double> Face;
            vector <Face> faces;
            vector <Face> faceNormals;

            // grab the IndexedFaceSets
            for (size_t i = 0; i < indices.size(); i++) {
                vector <IndexedFaceLines> vectorOfLines = indices[i].lines;
                for (size_t j = 0; j < vectorOfLines.size(); j++) {
                    vector <double> indices = vectorOfLines[j].indices;
                    assert (indices.size() == normalIndices.size());
                    //int startFace = indices[0];
                    // grab 1 triangle at a time.
                    Face aFace;
                    for (size_t k = 0; k < indices.size(); k++) {
                        if (indices[k] == -1) {
                            faces.push_back(aFace);
                            aFace.clear();
                            continue;
                        }
                        aFace.push_back(indices[k]);
                    }

                    Face nFace;
                    for (size_t k = 0; k < normalIndices.size(); k++) {
                        if (normalIndices[k] == -1) {
                            faceNormals.push_back(nFace);
                            nFace.clear();
                            continue;
                        }
                        nFace.push_back(normalIndices[k]);
                    }

                    // make sure we have the right amount of normal vectors that 
                    // match up with our faces.
                    assert (faces.size() == faceNormals.size());

                    for (size_t f = 0; f < faces.size(); f++) {
                        Face currentFace = faces[f];
                        Face currentNorm = faceNormals[f];
                        for (size_t c = 2; c < currentFace.size(); c++) {
                            int point1Idx = currentFace[0];
                            int point2Idx = currentFace[c-1];
                            int point3Idx = currentFace[c];

                            int normal1Idx = currentNorm[0];
                            int normal2Idx = currentNorm[c-1];
                            int normal3Idx = currentNorm[c];

                            drawFace(point1Idx, point2Idx, point3Idx,
                                     normal1Idx, normal2Idx, normal3Idx,
                                     xRes, yRes, 
                                     pointsTransformed, pointsWorldSpace,
                                     newNormals);

                        }
                    }
                }
            }

        } else if (block.blockType == 2) {
            //std::cerr << "Light" << std::endl;
            Light light = block.light;
            gLights.push_back(light);
            Vector3 location = light.location; // DEFAULT 0 0 1
            Vector3 color = light.color;  // DEFAULT 1 1 1
            //std::cerr << "LOCATION: " << location.x << " " << location.y << " " << location.z << std::endl;
            //std::cerr << "COLOR: " << color.x << " " << color.y << " " << color.z << std::endl;
        }
    }

    printImage(gImage);
    deallocImage(gImage);  // clean up image

    return 0;
}
