#include <iostream>
#include <cassert>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <stdlib.h>

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGl/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include "data.h"
#include "matrix.h"
#include "readpng.h"

#define RAD_TO_DEG 180/M_PI

const int NUM_POINTS=100;

using namespace std;

static int lastX, lastY;

int userTransformType;

CameraBlock gCamera;
vector <SeparatorBlock> gVectorSeparators;

GLuint *gTexNames; // will malloc space for texture names in main()
double gTao;
double gRippleSpeed = 0.03;
vector<Block> &parse_test(istream &datafile);

GLUquadricObj* gQuad;
Vec3 gSkyGridVertices[NUM_POINTS][NUM_POINTS];
std::vector <GLfloat> gSkyVertices;
std::vector <GLfloat> gSkyNormals;

/** PROTOTYPES **/
void redraw();
void initGL();
void resize(GLint w, GLint h);
void keyfunc(GLubyte key, GLint x, GLint y);
void drawObject(int separatorNumber);
void generateSkyVertices();
void generateSkyNormals();
void drawBackDrop();
void drawSky();
void setTexture(const std::string &fileName, int textureNumber);

/* Draws the current object, based on the current separator.
*/
void drawObject(int separatorNumber) 
{

    glPushMatrix();  // save the current matrix

    /*  // uncomment to draw X,Y,Z axes!
    float length = 3.0;
    glBegin (GL_LINES);
    glColor3d (1,0,0); // X axis is red.
    glVertex3d (0.0f, 0.0f, 0.0f);
    glVertex3d (length, 0.0 , 0.0 ); 
    glColor3d (0,1,0); // Y axis is green.
    glVertex3d (0.0, 0.0, 0.0);
    glVertex3d (0.0, length, 0.0);
    glColor3d (0,0,1); // z axis is blue.
    glVertex3d (0.0,0.0, 0.0);
    glVertex3d (0.0, 0.0, length); 
    glEnd();
    */

    SeparatorBlock &separator = gVectorSeparators[separatorNumber];
    vector <Transform> transforms = separator.transforms;
    vector <Coordinate3> points = separator.points;
    vector <IndexedFaceSet> indices = separator.indices;

    vector <Vector3> texCoords = separator.textureCoords;
    vector <double> texIndices = separator.textureIndices;

    std::vector <GLfloat> vectorVertices; // store the vertices and normals so we 
    std::vector <GLfloat> vectorTextures; // will be able to use VBO's!

    for (size_t i = 0; i < transforms.size(); i++) { // loop through Transform blocks
        Vec3 translationVector(0,0,0); // initialize vectors that don't change anything
        Vec3 rotationVector(0,0,0);  // stores the xyz of the rotation
        Vec3 scaleVector(1,1,1);

        double angle = 0; // store the rotation angle separately.

        Transform transform = transforms[i];
        vector <TransformCommand> transformations = transform.transformations;
        for (size_t j = 0; j < transformations.size(); j++) {
            TransformCommand transformCommand = transformations[j];
            string type = transformCommand.transformation;
            vector<double> args = transformCommand.data;
            if (type == "T") {
                translationVector = Vec3(args[0], args[1], args[2]);
            } else if (type == "R") {
                angle = args[3] * RAD_TO_DEG; // convert radians to degrees!
                rotationVector = Vec3(args[0], args[1], args[2]);
            } else if (type == "S") {
                scaleVector = Vec3(args[0], args[1], args[2]);
            }
        }
        // now, modify ModelView matrix by TRS
        glTranslatef(translationVector.x, translationVector.y, translationVector.z);
        glRotatef(angle, rotationVector.x, rotationVector.y, rotationVector.z);
        glScalef(scaleVector.x, scaleVector.y, scaleVector.z);
    }

    typedef vector <double> Face;
    vector <Face> faces;
    vector <Face> faceTextures;

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

            Face tFace;
            for (size_t k = 0; k < texIndices.size(); k++) {
                if (texIndices[k] == -1) {
                    faceTextures.push_back(tFace);
                    tFace.clear();
                    continue;
                }
                tFace.push_back(texIndices[k]);
            }

            for (size_t f = 0; f < faces.size(); f++) {
                Face currentFace = faces[f];
                //Face currentNorm = faceNormals[f];
                Face currentTexture = faceTextures[f];
                for (size_t c = 2; c < currentFace.size(); c++) {
                    int point1Idx = currentFace[0];
                    int point2Idx = currentFace[c-1];
                    int point3Idx = currentFace[c];

                    int texture1Idx = currentTexture[0];
                    int texture2Idx = currentTexture[c-1];
                    int texture3Idx = currentTexture[c];

                    Vector3 point1 = points[0].points[point1Idx];
                    Vector3 point2 = points[0].points[point2Idx];
                    Vector3 point3 = points[0].points[point3Idx];

                    Vector3 texture1 = texCoords[texture1Idx];
                    Vector3 texture2 = texCoords[texture2Idx];
                    Vector3 texture3 = texCoords[texture3Idx];

                    vectorVertices.push_back(point1.x);
                    vectorVertices.push_back(point1.y);
                    vectorVertices.push_back(point1.z);
                    vectorVertices.push_back(point2.x);
                    vectorVertices.push_back(point2.y);
                    vectorVertices.push_back(point2.z);
                    vectorVertices.push_back(point3.x);
                    vectorVertices.push_back(point3.y);
                    vectorVertices.push_back(point3.z);

                    vectorTextures.push_back(texture1.x);
                    vectorTextures.push_back(texture1.y);
                    vectorTextures.push_back(texture2.x);
                    vectorTextures.push_back(texture2.y);
                    vectorTextures.push_back(texture3.x);
                    vectorTextures.push_back(texture3.y);
                }
            }
        }
    }

    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, gTexNames[separatorNumber + 1]);
    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glTexCoordPointer( 2, GL_FLOAT, 0, &vectorTextures[0]); 
    glVertexPointer(3, GL_FLOAT, 0, &vectorVertices[0]);
    glDrawArrays(GL_TRIANGLES, 0, vectorVertices.size()/3); // do the draw
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisable(GL_TEXTURE_2D);

    glPopMatrix();  // restore old matrix.
}

void generateSkyVertices() 
{
    gSkyVertices.clear();
    
    for(int i = 0; i < NUM_POINTS; i++) {  
        for (int j = 0; j < NUM_POINTS; j++) {
            double x = -4 + 8 * (double)i/NUM_POINTS;
            double z = -4 + 8 * (double)j/NUM_POINTS;
            gSkyGridVertices[i][j] = Vec3(x, -1, z);
        }
    }

    // put into gl vertex array
    for (int i = 0; i < NUM_POINTS-1; ++i) { // loop through vertices 
        for (int j = 0; j < NUM_POINTS-1; ++j) {
            Vec3 &vertex0 = gSkyGridVertices[i][j];
            Vec3 &vertex1 = gSkyGridVertices[i][j+1];
            Vec3 &vertex2 = gSkyGridVertices[i+1][j+1];
            Vec3 &vertex3 = gSkyGridVertices[i+1][j];

            gSkyVertices.push_back(vertex0.x);  // grab vertices in order
            gSkyVertices.push_back(vertex0.y);
            gSkyVertices.push_back(vertex0.z);
            gSkyVertices.push_back(vertex1.x);
            gSkyVertices.push_back(vertex1.y);
            gSkyVertices.push_back(vertex1.z);
            gSkyVertices.push_back(vertex2.x);
            gSkyVertices.push_back(vertex2.y);
            gSkyVertices.push_back(vertex2.z);
            gSkyVertices.push_back(vertex3.x);
            gSkyVertices.push_back(vertex3.y);
            gSkyVertices.push_back(vertex3.z);
        }
    }
}

void generateSkyNormals() 
{
    Vec3 skyNormals[100][100];
    for(int i = 0; i < NUM_POINTS; i++) {  
        for (int j = 0; j < NUM_POINTS; j++) {

            double x = gSkyGridVertices[i][j].x;
            double z = gSkyGridVertices[i][j].z;

            double sinTerm = sin(x*x + z*z - gTao); // use gTao to make ripples outward
            double x_norm = 2 * x * sinTerm;
            double y_norm = 1.0;
            double z_norm = 2 * z * sinTerm;

            Vec3 normal(x_norm, y_norm, z_norm);
            normal.normalize();

            skyNormals[i][j] = normal;
        }
    }

    gSkyNormals.clear();
    // put into gl vertex array
    for (int i = 0; i < NUM_POINTS-1; ++i) {  // loop through normals
        for (int j = 0; j < NUM_POINTS-1; ++j) {
            Vec3 &normal0 = skyNormals[i][j];
            Vec3 &normal1 = skyNormals[i][j+1];
            Vec3 &normal2 = skyNormals[i+1][j+1];
            Vec3 &normal3 = skyNormals[i+1][j];

            gSkyNormals.push_back(normal0.x); // grab normals in order
            gSkyNormals.push_back(normal0.y);
            gSkyNormals.push_back(normal0.z);
            gSkyNormals.push_back(normal1.x);
            gSkyNormals.push_back(normal1.y);
            gSkyNormals.push_back(normal1.z);
            gSkyNormals.push_back(normal2.x);
            gSkyNormals.push_back(normal2.y);
            gSkyNormals.push_back(normal2.z);
            gSkyNormals.push_back(normal3.x);
            gSkyNormals.push_back(normal3.y);
            gSkyNormals.push_back(normal3.z);
        }
    }
}

void drawBackDrop() {
    gluQuadricOrientation(gQuad, GLU_INSIDE);

    glPushMatrix();  //
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    glTranslatef(0,0,-1);
    gluCylinder(gQuad, 3, 3, 100, 32, 32);
    glPopMatrix();
}

void drawSky() {

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_TEXTURE_GEN_S);
    glEnable(GL_TEXTURE_GEN_T);
    glBindTexture(GL_TEXTURE_2D, gTexNames[0]);

    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
    glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_NORMAL_ARRAY);
    glNormalPointer(GL_FLOAT, 0, &gSkyNormals[0]); 
    glVertexPointer(3, GL_FLOAT, 0, &gSkyVertices[0]);
    glDrawArrays(GL_QUADS, 0, gSkyVertices.size()/3); // do the draw!
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_NORMAL_ARRAY);

    drawBackDrop(); // draw backdrop as sky on a cylinder (using sphere mapping still)

    glDisable(GL_TEXTURE_2D);
    glDisable(GL_TEXTURE_GEN_S);
    glDisable(GL_TEXTURE_GEN_T);
}

// sets the texture stored in fileName
void setTexture(const std::string &fileName, int textureNumber) {

    std::string location = "hw6-data/";
    std::string filePath = location + fileName;

    int w, h;
    png_bytepp p = readpng(filePath.c_str(), &w, &h);

    unsigned char *data = new unsigned char [w * h * 3];

    for(int y=0; y<h; y++) {
        png_bytep r = p[h-1-y]; // get the row
        for (int x = 0; x < 3*w; x += 3) {
            int index = x + (3 * w * y);
            data[index] = r[x];
            data[index + 1] = r[x+1];
            data[index + 2] = r[x+2];
        }
    }

    glBindTexture(GL_TEXTURE_2D, gTexNames[textureNumber]);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); // use texture colors as is
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); // how pixels interpolated
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

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

    // Loop through separator blocks, and for each object (Seperator block), 
    // initialize the new material, and draw the object.
    for (size_t i = 0; i < gVectorSeparators.size(); i++) {
        drawObject(i);
    }
    drawSky();

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
    if (key == 27 || key == 'q' || key =='Q') {
        exit(0); // escape or q or Q to exit the program
    } else if (key == 'f' || key == 'F') {
        gRippleSpeed += 0.01; // increase the ripple speed
    } else if (key == 'g' || key == 'G') {
        if (gRippleSpeed >= 0.0099) {
            gRippleSpeed -= 0.01; // decrease ripple speed (but don't let it go negative)
        }
    } else if (key == 'r' || key == 'R') {
        glLoadIdentity(); // reset to inital position/orientation
        glRotatef(-gCamera.orientation.w * RAD_TO_DEG, gCamera.orientation.x, gCamera.orientation.y, gCamera.orientation.z);
        glTranslatef(-gCamera.position.x, -gCamera.position.y, -gCamera.position.z);
    }
}

/*
 * GLUT calls this function whenever there is any idle time.  Every time 
 * this gets called, we will modify gTao and recaculate the grid of sky 
 * normals, causing a rippling effect in our sky reflection.
 */
void idlefunc() 
{
    gTao += gRippleSpeed; // update global t
    generateSkyNormals(); // recalculate normals of sky reflection
    glutPostRedisplay(); // and then redraw
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

/**
 * Set up OpenGL state.  This does everything so when we draw we only need to
 * actually draw the sphere, and OpenGL remembers all of our other settings.
 */
void initGL()
{
    // Tell openGL to use gouraud shading:
    glShadeModel(GL_SMOOTH);
    
    // Enable back-face culling:
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Enable depth-buffer test.
    glEnable(GL_DEPTH_TEST);
    
    // Enable texture
    glEnable(GL_TEXTURE_2D);

    glDisable(GL_LIGHTING);  // note that we won't use lighting here.

    // Set up projection and modelview matrices ("camera" settings) 
    // Look up these functions to see what they're doing.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    checkGLError();

    // this is the only operation we are doing on GL_PROJECTION matrix
    glFrustum(gCamera.left, gCamera.right, gCamera.bottom, gCamera.top, gCamera.nearDistance, gCamera.farDistance);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // apply camera rotation -theta (make theta negative)
    // and then -translation (make x, y, z negative)
    // note: for rotation, angle must come as first argument, then x, y, z
    glRotatef(-gCamera.orientation.w * RAD_TO_DEG, gCamera.orientation.x, gCamera.orientation.y, gCamera.orientation.z);
    glTranslatef(-gCamera.position.x, -gCamera.position.y, -gCamera.position.z);

    // setup sky geometry
    generateSkyVertices();
    generateSkyNormals();

    // set up textures
    int numTextures = gVectorSeparators.size() + 1;  // +1 for sky
    gTexNames = (GLuint *)malloc(numTextures * sizeof(GLuint));
    glGenTextures(numTextures, gTexNames); // generate the necessary textures.

    setTexture("sky.png", 0); // set up sky texture image

    for (size_t i = 0; i < gVectorSeparators.size(); i++) {
        setTexture(gVectorSeparators[i].fileName, i+1); // +1 since 0 is for sky
    }

    gQuad = gluNewQuadric();
}

static void mouseButton(int button, int state, int x, int y) 
{
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                lastX = x;  // note where the drag began
                lastY = y;
                if (glutGetModifiers() == GLUT_ACTIVE_SHIFT) {
                    userTransformType = 1;  // "1" indicates ZOOM!        
                } else {
                    userTransformType = 0; // "0" indicates TRANSLATION!
                }
            } else if (state == GLUT_UP) {
                userTransformType = -1;  // reset
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            if (state == GLUT_DOWN) {
                lastX = x;
                lastY = y;
                userTransformType = -1; // reset
            } else if (state == GLUT_UP) {
                userTransformType = -1; // reset
            }
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN) {
                lastX = x;
                lastY = y; 
                userTransformType = 2;  // "2" indicates ROTATION!
            } else if (state == GLUT_UP) {
                userTransformType = -1; // reset
            }
            break;
    }
}       

static void motion(int x, int y) 
{
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
        //std::cout << "translate " << dx/100 << " " << -dy/100 << std::endl;
    } else if (userTransformType == 1) {
        glTranslatef(0, 0, -dy/100);  // Zooming - moves object in or out
    } 

    glMultMatrixf(&oldMatrix[0]);   // multiply by old matrix

    if (userTransformType == 2) { // Rotation - around axis of drag
        float length = sqrt(dx * dx + dy * dy);
        //std::cout << "length " << length;

        //glTranslatef(0, 0, -3);

        //float angle = length;
        //if (dx < 0) {
        //    angle *= -1;
        //}
        glRotatef(length/10, dy, dx, 0);
        //std::cout << ", axis " << -dy << " " << dx << std::endl;
        //glTranslatef(0, 0, 3);  // 3 units in front of camera
    }

    glutPostRedisplay();
}

/**
 * Sets up some stuff then passes control to glutMainLoop() which never
 * returns.
 */
int main(int argc, char* argv[])
{

    if (argc != 3) {
        std::cerr << "USAGE: " << argv[0] << " xRes yRes < .iv file" << std::endl;
        exit(1);
    }

    int xRes = atoi(argv[1]);
    int yRes = atoi(argv[2]);

    assert(xRes >= 0);
    assert(yRes >= 0);


    vector<Block> &blocks = parse_test(cin);

    
    for (size_t i = 0; i < blocks.size(); i++) {
        Block block = blocks[i];
        if (block.blockType == 0) {
            gCamera = block.camera;
        } else if (block.blockType == 1) {
            SeparatorBlock separator = block.separator;
            gVectorSeparators.push_back(separator);
        }
        else if (block.blockType == 2) {
            // note: not expected any lights for this assignment, since we use textures
            //Light light = block.light;
            //gLights.push_back(light);
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

    glutCreateWindow("CS171 HW6");
    
    initGL();

    // set up GLUT callbacks.
    glutDisplayFunc(redraw);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyfunc);

    glutMouseFunc(mouseButton);
    glutMotionFunc(motion);
    glutIdleFunc(idlefunc);

    // From here on, GLUT has control,
    glutMainLoop();
    
    // so we should never get to this point.
    return 1;
}

