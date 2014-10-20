#include <iostream>
#include <cassert>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include "data.h"
#include "matrix.h"
#include <stdlib.h>

#ifdef MACOSX
#include "OpenGL/gl.h"
#include "OpenGl/glu.h"
#include "GLUT/glut.h"
#else
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#endif

using namespace std;

static int lastX, lastY;

int userTransformType;

CameraBlock gCamera;
vector <SeparatorBlock> gVectorSeparators;
SeparatorBlock gSeparator;
vector <Light> gLights;
Material gMaterial;
vector<Block> &parse_test(istream &datafile);

/* 
 * A quadric can be a cylinder, disk, sphere, cone, etc.
 * We just reuse this memory space each time we draw any sort of quad.
 * GLU supplies this funcionality.
 */
GLUquadricObj* quad;

/** PROTOTYPES **/
void initLights();
void initMaterial();
void redraw();
void initGL();
void resize(GLint w, GLint h);
void keyfunc(GLubyte key, GLint x, GLint y);

void drawObject() {

    glPushMatrix();  // save the current matrix

    vector <Transform> transforms = gSeparator.transforms;
    vector <Coordinate3> points = gSeparator.points;
    vector <IndexedFaceSet> indices = gSeparator.indices;

    vector <Vector3> normals = gSeparator.normals;
    vector <double> normalIndices = gSeparator.normalIndices;



    for (size_t i = 0; i < transforms.size(); i++) { // loop through Transform blocks

            Matrix transformResult = Matrix(4,4);  // start with identity 4x4
            Matrix normalTransform = Matrix(4,4);
            Matrix normalTransformInverse = Matrix(4,4);
            Matrix normalTransformInverseTranpose = Matrix(4,4);

            Matrix translation = Matrix(4,4);
            Matrix rotation = Matrix(4,4);
            Matrix scaleFactor = Matrix(4,4);

            Vec3 translationVector(1.0,1.0,1.0); // initialize vectors that don't change anything
            Vec3 rotationVector(1,1,1);  // stores the xyz of the rotation
            Vec3 scaleVector(1,1,1);

            double angle = 0; // store the rotation angle seperately.

            Transform transform = transforms[i];
            vector <TransformCommand> transformations = transform.transformations;
            for (size_t j = 0; j < transformations.size(); j++) {
                TransformCommand transformCommand = transformations[j];
                string type = transformCommand.transformation;
                vector<double> args = transformCommand.data;
                if (type == "T") {
                    Matrix T = Matrix(4,4);
                    T.translationMatrix(args[0], args[1], args[2]);
                    translationVector.x = args[0];
                    translationVector.y = args[1];
                    translationVector.z = args[2];
                    //std::cerr << "T=" << std::endl;
                    //T.print();
                    translation = T;
                } else if (type == "R") {
                    Matrix R = Matrix(4,4);
                    R.rotationMatrix(args[0], args[1], args[2], args[3]);
                    angle = args[3] * 57.2958; // convert radians to degrees!
                    rotationVector.x = args[0];
                    rotationVector.y = args[1];
                    rotationVector.z = args[2];
                    //std::cerr << "R=" << std::endl;
                    //R.print();
                    rotation = R;
                } else if (type == "S") {
                    Matrix S = Matrix(4,4);
                    S.scaleFactorMatrix(args[0], args[1], args[2]);
                    scaleVector.x = args[0];
                    scaleVector.y = args[1];
                    scaleVector.z = args[2];
                    //std::cerr << "S=" << std::endl;
                    //S.print();
                    scaleFactor = S;
                }
            }
            // now, modify ModelView matrix by TRS
            glTranslatef(translationVector.x, translationVector.y, translationVector.z);
            glRotatef(angle, rotationVector.x, rotationVector.y, rotationVector.z);
            glScalef(scaleVector.x, scaleVector.y, scaleVector.z);
    }

    // grab the Coordinate3 points, and transform them to x,y pixels
    for (size_t i = 0; i < points.size(); i++) {
        vector <Vector3> vectorOfPoints = points[i].points;
        for (size_t j = 0; j < vectorOfPoints.size(); j++) {
            Vector3 vect = vectorOfPoints[j];
            //std::cout << "vect3: " << vect.x << vect.y << vect.z << std::endl;
        }
    }
    // points[0].points[i] will give ith point

    typedef vector <double> Face;
    vector <Face> faces;
    vector <Face> faceNormals;

    // grab the IndexedFaceSets
    for (size_t i = 0; i < indices.size(); i++) {
        vector <IndexedFaceLines> vectorOfLines = indices[i].lines;
        for (size_t j = 0; j < vectorOfLines.size(); j++) {
            vector <double> indices = vectorOfLines[j].indices;

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

                    Vector3 point1 = points[0].points[point1Idx];
                    Vector3 point2 = points[0].points[point2Idx];
                    Vector3 point3 = points[0].points[point3Idx];

                    Vector3 norm1 = normals[normal1Idx];
                    Vector3 norm2 = normals[normal2Idx];
                    Vector3 norm3 = normals[normal3Idx];

                    double norm_x = (norm1.x + norm2.x + norm3.x) / 3;
                    double norm_y = (norm1.y + norm2.y + norm3.y) / 3;
                    double norm_z = (norm1.z + norm2.z + norm3.z) / 3;
                    glBegin(GL_TRIANGLES);
                    glNormal3d(norm_x, norm_y, norm_z);
                    glVertex3d(point1.x, point1.y, point1.z);
                    glVertex3d(point2.x, point2.y, point2.z);
                    glVertex3d(point3.x, point3.y, point3.z);
                    glEnd();
                }
           }
            //assert (indices.size() == normalIndices.size());
        }
    }
    glPopMatrix();  // restore old matrix.


}

/** GLUT callback functions **/

/*
 * This function gets called every time the window needs to be updated
 * i.e. after being hidden by another window and brought back into view,
 * or when the window's been resized.
 * You should never call this directly, but use glutPostRedisply() to tell
 * GLUT to do it instead.
 */
void redraw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for (size_t i = 0; i < gVectorSeparators.size(); i++) {
        gSeparator = gVectorSeparators[i];
        gMaterial = gSeparator.material;  // update current material
        initMaterial();
        drawObject();
    }

    //gluSphere(quad, 1.0, 256, 256);

    // TODO: for seperator in seperatorBlocks...draw object!
    // init Material based on seperator block
    // drawObjects based on seperator block

    /*  // EXAMPLE TO TEST ROTATION
    glBegin(GL_QUADS);
 
    glColor3f(1.0f, 0.0f, 0.0f);
    // FRONT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f( 0.5f, -0.5f, 0.5f);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    // BACK
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    
    glColor3f(0.0f, 1.0f, 0.0f);
    // LEFT
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    // RIGHT
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f( 0.5f, -0.5f, 0.5f);
     
    glColor3f(0.0f, 0.0f, 1.0f);
    // TOP
    glVertex3f(-0.5f, 0.5f, 0.5f);
    glVertex3f( 0.5f, 0.5f, 0.5f);
    glVertex3f( 0.5f, 0.5f, -0.5f);
    glVertex3f(-0.5f, 0.5f, -0.5f);
    // BOTTOM
    glVertex3f(-0.5f, -0.5f, 0.5f);
    glVertex3f(-0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, -0.5f);
    glVertex3f( 0.5f, -0.5f, 0.5f);
    glEnd();
    */

    glutSwapBuffers();
}

/**
 * GLUT calls this function when the window is resized.
 * All we do here is change the OpenGL viewport so it will always draw in the
 * largest square that can fit in our window..
 */
void resize(GLint w, GLint h)
{
    if (h == 0)
        h = 1;

    // ensure that we are always square (even if whole window not used)
    if (w > h)
        w = h;
    else
        h = w;

    // Reset the current viewport and perspective transformation
    glViewport(0, 0, w, h);

    // Tell GLUT to call redraw()
    glutPostRedisplay();
}

/*
 * GLUT calls this function when any key is pressed while our window has
 * focus.  Here, we just quit if any appropriate key is pressed.  You can
 * do a lot more cool stuff with this here.
 */
void keyfunc(GLubyte key, GLint x, GLint y)
{
    // escape or q or Q
    if (key == 27 || key == 'q' || key =='Q')
        exit(0);
}

// call this to see if there's any GL error, if there is,
// print out the error
void checkGLError()
{
    GLenum error = glGetError();
    if (error != GL_NO_ERROR) {
        std::cerr << "glError " << gluErrorString(error) << std::endl;
    }
}

// printmatrix
// Prints the given matrix
// Assumes column-major format, as in OpenGL
void printMatrix(GLdouble thematrix[16])
{
   int i, j;  // MS-Vis C++ 6.0 sometimes chokes on var's
              //  declared in for's.

   for (i=0; i<4; ++i)     // i = row
   {
      for (j=0; j<4; ++j)  // j = column
      {
         cout << fixed << setprecision(4) << setw(7)
               << thematrix[j*4+i] << " ";
      }
      cout << endl;
   }
}

/** Utility functions **/


/**
 * Returns a Glenum corresponding to the correct light given an index. 
 */
 GLenum getLight(size_t i) {
    if (i == 0) {
        return GL_LIGHT0;
    } else if (i == 1) {
        return GL_LIGHT1;
    } else if (i == 2) {
        return GL_LIGHT2;
    } else if (i == 3) {
        return GL_LIGHT3;
    } else if (i == 4) {
        return GL_LIGHT4;
    } else if (i == 5) {
        return GL_LIGHT5;
    } else if (i == 6) {
        return GL_LIGHT6;
    } else if (i == 7) {
        return GL_LIGHT7;
    } else {
        std::cerr << "Can't get right light!" << std::endl;
        return GL_LIGHT0;
    }
 }

/**
 * Sets up an OpenGL light.  This only needs to be called once
 * and the light will be used during all renders.
 */
void initLights() {

    for (size_t i = 0; i < gLights.size(); i++) {
        std::cout << "LIGHT" << std::endl;
        Light light = gLights[i];
        Vec3 scolor(gMaterial.specular.x, gMaterial.specular.y, gMaterial.specular.z);
        Vec3 dcolor(gMaterial.diffuse.x, gMaterial.diffuse.y, gMaterial.diffuse.z);
        Vec3 ambient(0,0,0);

        Vec3 lx(light.location.x, light.location.y, light.location.z);

        int b = int(i);

        std::ostringstream lightName;
        lightName << "GL_LIGHT" << b;
        std::cout << lightName.str() << std::endl;

        GLfloat amb[] = { 0.0f, 0.0f, 0.0f, 0.0f };
        GLfloat diff[]= { light.color.x, light.color.y, light.color.z, 1.0f };
        GLfloat spec[]= { light.color.x, light.color.y, light.color.z, 1.0f };
        GLfloat lightpos[]= { lx.x, lx.y, lx.z, 1.0f };
        //GLfloat lightpos[]= { 2.0f, 2.0f, 5.0f, 1.0f };
        std::cout << lx.x << lx.y << lx.z << std::endl;
        GLfloat shiny = 4.0f; // TODO: what to do about light shininess?
        checkGLError();

        GLenum lightNumber = getLight(i);
        glLightModelfv(GL_LIGHT_MODEL_AMBIENT, amb);
        glLightfv(lightNumber, GL_AMBIENT, amb);
        glLightfv(lightNumber, GL_DIFFUSE, diff);
        glLightfv(lightNumber, GL_SPECULAR, spec);
        glLightfv(lightNumber, GL_POSITION, lightpos);
        glLightf(lightNumber, GL_SHININESS, shiny);
        glEnable(lightNumber);
    }

    // Turn on lighting.  You can turn it off with a similar call to
    // glDisable().
    glEnable(GL_LIGHTING);
}

/**
 * Sets the OpenGL material state.  This is remembered so we only need to
 * do this once.  If you want to use different materials, you'd need to do this
 * before every different one you wanted to use.
 */
void initMaterial() {
    GLfloat emit[] = {0.0, 0.0, 0.0, 1.0};
    GLfloat  amb[] = {gMaterial.ambient.x, gMaterial.ambient.y, gMaterial.ambient.z, 1.0};
    GLfloat diff[] = {gMaterial.diffuse.x, gMaterial.diffuse.y, gMaterial.diffuse.z, 1.0};
    GLfloat spec[] = {gMaterial.specular.x, gMaterial.specular.y, gMaterial.specular.z, 1.0};
    GLfloat shiny = gMaterial.shininess;

    glMaterialfv(GL_FRONT, GL_AMBIENT, amb);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diff);
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_EMISSION, emit);
    glMaterialfv(GL_FRONT, GL_SHININESS, &shiny);
}

/**
 * Set up OpenGL state.  This does everything so when we draw we only need to
 * actually draw the sphere, and OpenGL remembers all of our other settings.
 */
void initGL()
{
    // Tell openGL to use gauraud shading:
    glShadeModel(GL_SMOOTH);
    
    // Enable back-face culling:
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Enable depth-buffer test.
    glEnable(GL_DEPTH_TEST);
    
    // Set up projection and modelview matrices ("camera" settings) 
    // Look up these functions to see what they're doing.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    //glFrustum(-0.5, 0.5, -0.5, 0.5, 1, 10);
    GLdouble matrixFrustrum[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrixFrustrum);
    checkGLError();
    //printMatrix(matrixFrustrum);
    std::cout << "L: "<< gCamera.left << " R:" << gCamera.right << " B: " << gCamera.bottom
        << " T:" << gCamera.top << " N:" << gCamera.nearDistance << " F:" << gCamera.farDistance << std::endl;
    glFrustum(gCamera.left, gCamera.right, gCamera.bottom, gCamera.top, gCamera.nearDistance, gCamera.farDistance);
    //double matrixFrustrum[16];
    glGetDoublev(GL_PROJECTION_MATRIX, matrixFrustrum);
    std::cout << matrixFrustrum[0] << std::endl;
    printMatrix(matrixFrustrum);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // apply camera rotation and then translation
    // note: angle must come as first argument, then x, y, z
    glRotatef(gCamera.orientation.w * 57.2958, gCamera.orientation.x, gCamera.orientation.y, gCamera.orientation.z);
    glTranslatef(gCamera.position.x, gCamera.position.y, gCamera.position.z);


    //gluLookAt(5, 5, 5, 0, 0, 0, 1, 0, 0);
    gluLookAt(-2, 0, 5, 0, 0, 0, 1, 0, 0);

    // set light parameters
    initLights();

    // set material parameters
    initMaterial();

    // initialize the "quadric" used by GLU to render high-level objects.
    quad = gluNewQuadric();
    gluQuadricOrientation(quad, GLU_OUTSIDE);
}

static void mouseButton(int button, int state, int x, int y) {
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                lastX = x;  // note where the drag began
                lastY = y;
                std::cout << "LEFT DOWN" << std::endl;
                if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
                    std::cout << "SHIFT" << std::endl;  
                    userTransformType = 1;  // "1" indicates ZOOM! // TODO: MOVE TO MIDDLE MOUSE         
                } else {
                    userTransformType = 0; // "0" indicates TRANSLATION! // TODO: MOVE TO MIDDLE MOUSE
                }
            } else if (state == GLUT_UP) {
                userTransformType = -1;  // reset
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN) {
                std::cout << "MIDDLE DOWN" << std::endl;
                lastX = x;
                lastY = y;
            } else if (state == GLUT_UP) {
                userTransformType = -1; // reset
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN) {
                std::cout << "RIGHT DOWN" << std::endl;
                lastX = x;
                lastY = y; 
                userTransformType = 2;
            } else if (state == GLUT_UP) {
                userTransformType = -1; // reset
            }
            break;
    }
}       

static void motion(int x, int y) {
    double dy = y-lastY;
    double dx = x-lastX;
    lastX = x;
    lastY = y;

    // TODO: set RIGHT MOUSE BUTTON to a different type so nothing happens
    if (!(userTransformType == 0 || userTransformType == 1 || userTransformType == 2)) {
        return;
    }

    glMatrixMode(GL_MODELVIEW);

    GLfloat oldMatrix[16];  // copy current modelview matrix
    glGetFloatv(GL_MODELVIEW_MATRIX, &oldMatrix[0]);
    glLoadIdentity();  // start over at identity
    
    // apply mouse transforms here
    if (userTransformType == 0) {
        glTranslatef(dx/100, -dy/100, 0); // Transformations - used for panning around
    } else if (userTransformType == 1) {
        glTranslatef(0, 0, -dy/100);  // Zooming - moves object in or out
    } 

    glMultMatrixf(&oldMatrix[0]);   // multiply by old matrix

    if (userTransformType == 2) {
        //double sq = sqrt(dx*dx + dy*dy);
        //glRotatef(sq, dx/50, dy/50, 3);
        glRotatef(dx, 1.0f, 0.0f, 0.0f); // TODO: make rotation better?
        glRotatef(dy, 0.0f, 1.0f, 0.0f);
    }




    //theta += dx;
    //rho += dy;

    //rho = clip(rho, -90, 90);
    glutPostRedisplay();
}

/**
 * Main entrance point, obviously.
 * Sets up some stuff then passes control to glutMainLoop() which never
 * returns.
 */
int main(int argc, char* argv[])
{

    if (argc != 3) {
        std::cerr << "USAGE: oglRenderer [xRes] [yRes] < [.iv file] " << std::endl;
        exit(1);
    }

    int xRes = atoi(argv[1]);
    int yRes = atoi(argv[2]);


    assert(xRes >= 0);
    assert(yRes >= 0);

    //gImage = allocImage(xRes, yRes);  // setup image
    //initImage(gImage);

    vector<Block> &blocks = parse_test(cin);

    for (size_t i = 0; i < blocks.size(); i++) {
        Block block = blocks[i];
        if (block.blockType == 0) {

            gCamera = block.camera;

            /*
            Matrix T = Matrix(4,4);
            T.translationMatrix(block.camera.position.x, block.camera.position.y, block.camera.position.z);

            Matrix R = Matrix(4,4);
            R.rotationMatrix(block.camera.orientation.x, block.camera.orientation.y, block.camera.orientation.z, block.camera.orientation.w);

            Camera *= T;
            Camera *= R;

            CameraInverse = Camera;
            CameraInverse = CameraInverse.invert();
            */

        } else if (block.blockType == 1) {
            SeparatorBlock separator = block.separator;
            gSeparator = separator;
            gVectorSeparators.push_back(gSeparator);
            Material material = separator.material;
            gMaterial = material;
        }
        else if (block.blockType == 2) {
            Light light = block.light;
            gLights.push_back(light);
        }
    }


    // OpenGL will take out any arguments intended for its use here.
    // Useful ones are -display and -gldebug.
    glutInit(&argc, argv);

    // Get a double-buffered, depth-buffer-enabled window, with an
    // alpha channel.
    // These options aren't really necessary but are here for examples.
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(xRes, yRes);
    glutInitWindowPosition(300, 100);

    glutCreateWindow("CS171 HW4");
    
    initGL();

    // set up GLUT callbacks.
    glutDisplayFunc(redraw);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyfunc);

    glutMouseFunc(mouseButton);
    glutMotionFunc(motion);

    // From here on, GLUT has control,
    glutMainLoop();

    // so we should never get to this point.
    return 1;
}

