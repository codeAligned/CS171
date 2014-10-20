#include <iostream>
#include <list>
#include <vector>
#include <cassert>
#include "stdlib.h"
#include "data.h"
#include "matrix.h"

using namespace std;

vector<Block> &parse_test(istream &datafile);

// makes the pixel at (x,y) on the canvas a white pixel
void drawPixel(int x, int y, Image *image) {
    //std::cout << "X: " << x << " Y: " << y << std::endl;
    assert (x >= 0 && x < image->width);
    assert (y >= 0 && y < image->height);
    Pixel p;
    p.r = p.g = p.b = 255;
    image->canvas[image->height - 1 - y][x] = p;
}

void Bresenham(double x1, double y1, double x2, double y2, bool swap, Image *image) {
    // Reverse lines where x1 > x2
    // maintaining value of swap
    //std::cout << x1 << " " << y1 << " " << x2 << " " << y2 << std::endl;
    if (x1 > x2) {
        if (swap) {
            Bresenham(x2, y2, x1, y1, true, image);
        } else {
            Bresenham(x2, y2, x1, y1, false, image);
        }
        return;
    }

    // special case for vertical line (undefined slope)
    if (x1 == x2) {
        if (y2 >= y1) {
            for (int y = y1; y <= y2; y++) {
                //std::cout << "aX: " << x1 << " Y: " << y << std::endl;
                drawPixel(x1, y, image);
            }
        } else {
            for (int y = y2; y <= y1; y++) {
                //std::cout << "aX: " << x1 << " Y: " << y << std::endl;
                drawPixel(x1, y, image);
            } 
        }
        return;
    }

    // special case for horizontal line (slope = 0)
    if (y1 == y2) {
        for (int x = x1; x <= x2; x++) {
            drawPixel(x, y1, image);
        }
        return;
    }


    int y = y1;

    // positive slope case
    if ((y2 - y1) >= 0) {
        if ((x2 - x1) < (y2 - y1)) {  // slope bigger than 1. swap x and y
            Bresenham(y1, x1, y2, x2, true, image);
            return;
        }

        int dy = y2 - y1;
        int dxdy = y2 - y1 + x1 - x2;
        int F = y2 - y1 + x1 - x2;
        for (int x = x1; x <= x2; x++) {
            if (swap) {
                //std::cout << "bX: " << y << " Y: " << x << std::endl;
                drawPixel(y, x, image);
            } else {
                //std::cout << "cX: " << x << " Y: " << y << std::endl;
                drawPixel(x, y, image);
            }
            if (F < 0) {
                F += dy;
            } else {
                y++;
                F += dxdy;
            }
        }
    } else {    // negative slope case
        if ((x2 - x1) < (y1 - y2)) {  // slope steeper than -1. swap x and y
            Bresenham(y1, x1, y2, x2, true, image);
            return;
        }

        int dy = y1 - y2;        
        int dxdy = y1 - y2 + x1 - x2;
        int F = y1 - y2 + x1 - x2;
        for (int x = x1; x <= x2; x++) {
            if (swap) {
                //std::cout << "dX: " << y << " Y: " << x << std::endl;
                drawPixel(y, x, image);
            } else {
                //std::cout << "eX: " << x << " Y: " << y << std::endl;
                drawPixel(x, y, image);
            }
            if (F < 0) {
                F += dy;
            } else {
                y--;
                F += dxdy;
            }
        }
    }
}

/* given a value of the endpont of a line on a scale from min to max, 
map it to the pixel of the image of size resolution */
int getPixel(double value, double min, double max, double resolution) {

    float valuePerPixel = (value - min) / (max - min);

    /* note that we really want to map from 0 to (resolution - 1), which
    is the maximum size of our array */
    float pixel = valuePerPixel * (resolution - 1);
    return pixel;
}


int main(int argc, char* argv[])
{
    
    if (argc != 3) {
        std::cout << "USAGE: wireframe [xRes] [yRes]" << std::endl;
        exit(1);
    }

    double xmin = -1; // in NDC everything between -1 and 1
    double xmax = 1;
    double ymin = -1;
    double ymax = 1;
    double xRes = atof(argv[1]);
    double yRes = atof(argv[2]);

    assert(xmin <= xmax);
    assert(ymin <= ymax);
    assert(xRes >= 0);
    assert(yRes >= 0);


    Image image;
    image.width = xRes;
    image.height = yRes;
    image.canvas = (Pixel**) malloc(image.height * (sizeof(Pixel*)));
    for (int i = 0; i < image.width; i++) {
        image.canvas[i] = (Pixel*) malloc(image.width * (sizeof(Pixel)));
    }

    // Zero out all pixels on the canvas
    Pixel black;
    black.r = black.g = black.b = 0;
    for (int i = 0; i < image.height; i++) {
        for (int j = 0; j < image.width; j++) {
            image.canvas[i][j] = black;
        }
    }
    
    

    vector<Block> &blocks = parse_test(cin);

    Matrix Camera = Matrix(4,4);
    Matrix CameraInverse = Matrix(4,4);
    Matrix Perspective = Matrix(4,4);


    for (size_t i = 0; i < blocks.size(); i++) {
        Block block = blocks[i];
        if (block.blockType == 0) {

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

        } else {
            SeparatorBlock separator = block.separator;
            vector <Transform> transforms = separator.transforms;
            vector <Coordinate3> points = separator.points;
            vector <IndexedFaceSet> indices = separator.indices;

            // we will multiple the result of every Transform block to get
            // the final transform
            Matrix finalTransformResult = Matrix(4,4);  // start with identity 4x4

            for (size_t i = 0; i < transforms.size(); i++) { // loop through Transform blocks

                Matrix transformResult = Matrix(4,4);  // start with identity 4x4

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
                        translation = T;
                    } else if (type == "R") {
                        Matrix R = Matrix(4,4);
                        R.rotationMatrix(args[0], args[1], args[2], args[3]);
                        rotation = R;
                    } else if (type == "S") {
                        Matrix S = Matrix(4,4);
                        S.scaleFactorMatrix(args[0], args[1], args[2]);
                        scaleFactor = S;
                    }
                }
                // multiple in correct order: S = TRS
                transformResult *= translation;
                transformResult *= rotation;
                transformResult *= scaleFactor;

                // multiple the final transform by the result of this transform block
                finalTransformResult *= transformResult;
            }

            vector <Point> pointsTransformed;
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
                    y /= w; // ignore z. will just use new x and y coordinates
                    struct Point p;
                    p.x = x;
                    p.y = y;
                    pointsTransformed.push_back(p);
                }
            }

            // grab the IndexedFaceSets
            for (size_t i = 0; i < indices.size(); i++) {
                vector <IndexedFaceLines> vectorOfLines = indices[i].lines;
                for (size_t j = 0; j < vectorOfLines.size(); j++) {
                    vector <double> indices = vectorOfLines[j].indices;
                    int startFace = indices[0];
                    for (size_t k = 1; k < indices.size(); k++) {
                        if (indices[k] == -1) { // end of face. connect back to first vertex of face
                            int indexStartPoint = indices[k-1];
                            int indexEndPoint = startFace;
                            startFace = -1;
                            double x1 = getPixel(pointsTransformed[indexStartPoint].x, xmin, xmax, xRes);
                            double y1 = getPixel(pointsTransformed[indexStartPoint].y, ymin, ymax, yRes);
                            double x2 = getPixel(pointsTransformed[indexEndPoint].x, xmin, xmax, xRes);
                            double y2 = getPixel(pointsTransformed[indexEndPoint].y, ymin, ymax, yRes);
                            Bresenham(x1, y1, x2, y2, false, &image);
                        } else {
                            if (startFace == -1) {  // starting a new face. no line to connect.
                                startFace = indices[k];
                            } else {
                                int indexStartPoint = indices[k-1];
                                int indexEndPoint = indices[k];
                                double x1 = getPixel(pointsTransformed[indexStartPoint].x, xmin, xmax, xRes);
                                double y1 = getPixel(pointsTransformed[indexStartPoint].y, ymin, ymax, yRes);
                                double x2 = getPixel(pointsTransformed[indexEndPoint].x, xmin, xmax, xRes);
                                double y2 = getPixel(pointsTransformed[indexEndPoint].y, ymin, ymax, yRes);
                                Bresenham(x1, y1, x2, y2, false, &image);
                            }
                        }
                    }
                }
            }

        }
    }


    /* Output some header info for the PPM file */
    
    std::cout << "P3" << std::endl;
    std::cout << xRes << " " << yRes << std::endl;
    std::cout << "255" << std::endl;
    std::cout << " " << std::endl;

    for (int i = 0; i < image.height; ++i) {
        for (int j = 0; j < image.width; ++j) {
            std::cout << image.canvas[i][j].r << " " << image.canvas[i][j].g << " " << image.canvas[i][j].b << std::endl;
        }
    } 

    for (int i = 0; i < image.width; i++) {
        free(image.canvas[i]);
    }
    free(image.canvas);

    return 0;
}
