#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include "data.h"
#include "matrix.h"
#include <stdlib.h>
//#include "readpng.h"

#ifdef __APPLE__
#include "OpenGL/gl.h"
#include "OpenGl/glu.h"
#include "GLUT/glut.h"
#else
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#endif

#define RAD_TO_DEG 180.0/M_PI
#define DEG_TO_RAD M_PI/180.0

using namespace std;

int drawingType;

Vec3 gCameraPosition;
float gTheta = 90.0;
float gCameraDistance = 3.0;

vector <SeparatorBlock> gVectorSeparators;

vector<Keyframe> gKeyframes;
int gNumberOfFrames;
int gCurrentFrame;
int gUserInput;
int gLoopMode;
int gPlaybackMode;
string gInputString = "";
int gAnimationSpeed = 70; // start close to 24 fps
vector<Keyframe> &parse_test(istream &datafile);

/* 
 * A quadric can be a cylinder, disk, sphere, cone, etc.
 * We just reuse this memory space each time we draw any sort of quad.
 * GLU supplies this funcionality.
 */
GLUquadricObj* gQuad;

/** PROTOTYPES **/
void redraw();
void initGL();
void resize(GLint w, GLint h);
void keyfunc(GLubyte key, GLint x, GLint y);

/* Draws the string at the specified position on the screen. 
 * Give coords in NDC. Call as: drawBitmapText("Hello world",-0.9,-0.9,0)
 */
void drawBitmapText(const char *string, float x, float y, float z)
{
    const char *c;
    glRasterPos3f(x,y,z);

    glColor3d (1,1,0); // text will be yellow!

    for (c=string; *c != '\0'; c++)
    {
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, *c);
    }
    //glPopMatrix();
}

void drawAxes()
{
    float length = 5;
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
}

/* Draws the actual object we are animating.  Note that transformations should 
 * already be applied before calling this function. */
void drawIBar()
{
    glPushMatrix();

    float radius= .1;
    float length = 1;

    glColor3d (0,1,1); // this segment is teal.
    glPushMatrix();
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(gQuad, radius, radius, length, 32, 32);
    glPopMatrix();

    glColor3d(1,1,1); // this segment is white.
    glPushMatrix();
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(gQuad, radius, radius, length, 32, 32);
    glPopMatrix();

    glColor3d(1,1,0); // this segment is yellow
    glPushMatrix();
    glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
    gluCylinder(gQuad, radius, radius, length, 32, 32);
    glPopMatrix();

    glColor3d(1,0,1); // this segment is magenta
    glPushMatrix();
    glTranslatef(length, 0.0f, 0.0f);
    glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(gQuad, radius, radius, length, 32, 32);
    glPopMatrix();

    glColor3d(0.75,0.75,0.75); // this segment is gray
    glPushMatrix();
    glTranslatef(length, 0.0f, 0.0f);
    glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
    gluCylinder(gQuad, radius, radius, length, 32, 32);
    glPopMatrix();

    glPopMatrix();  // restore, since keyframes do not combine
}

/* Draws frame specific information in corners of window */
void drawText(int i, Vector3 &T, Vector4 &R, Vector3 &S) {
    char frame[256];  // allocate some space to store the string
    sprintf(frame, "Frame: %d", i);
    char totalFrames[256];  // allocate some space to store the string
    sprintf(totalFrames, "Out of %d Frames", gNumberOfFrames);
    drawBitmapText("", 0, 0, 0);
    drawBitmapText(frame,-29.75,-28.50,-3);
    drawBitmapText(totalFrames,-29.75,-29.75, -3);
    if (gLoopMode == 1) {
        drawBitmapText("Looping", 23.0, -29.50, -3);
    }
    if (gPlaybackMode) {
        drawBitmapText("Playing Animation", 18.00, -28.0, -3);   
    }

    char translation[256];
    sprintf(translation, "Translation: X: %f Y: %f Z: %f", T.x, T.y, T.z);
    drawBitmapText(translation, -29.75, 28.00, -3);

    char rotation[256];
    sprintf(rotation, "Rotation: X: %f Y: %f Z: %f Angle: %f", R.x, R.y, R.z, R.w);
    drawBitmapText(rotation, -29.75, 26.00, -3);

    char scale[256];
    sprintf(scale, "Scale: X: %f Y: %f Z: %f", S.x, S.y, S.z);
    drawBitmapText(scale, -29.75, 24.00, -3);
}

/* Draw the current frame */
void drawFrame(int i) {

    // do this frame's TRS, and draw the IBar before restoring the old matrix
    Keyframe key = gKeyframes[i];
    Vector3 T = key.translation;
    Vector4 R = key.rotation;
    Vector3 S = key.scaleFactor;
    glPushMatrix();
    glLoadIdentity();
    drawText(i, T, R, S);  // write frame info in corners of window
    glPopMatrix();

    glPushMatrix(); // save the current

    glTranslatef(T.x, T.y, T.z);
    glRotatef(R.w, R.x, R.y, R.z);
    glScalef(S.x, S.y, S.z);

    drawIBar();

    glPopMatrix();  // restore, since keyframes do not combine
}

/* Draws the current object */
void drawObject() 
{
    // Clear Color and Depth Buffers
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
    glLoadIdentity();

    gCameraPosition.x = gCameraDistance * cos(gTheta * DEG_TO_RAD);
    gCameraPosition.y = 0.0;
    gCameraPosition.z = gCameraDistance * sin(gTheta * DEG_TO_RAD);

    // Set the camera
    gluLookAt( gCameraPosition.x, gCameraPosition.y, gCameraPosition.z,
               0.0f, 0.0f, 0.0f,
               0.0f, 1.0f, 0.0f);

    drawFrame(gCurrentFrame);

    if (drawingType != 0) {
        drawAxes();
    }
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

    drawObject();

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

/* The callback function that is used for animation, updating the current frame
 * every time it is called */
void Timer(int i) {
    if (!gPlaybackMode) {
        return; // don't do anything if we are not in playback mode.
    }
    if (gCurrentFrame < gNumberOfFrames) {
        gCurrentFrame += 1;
        glutPostRedisplay();
        glutTimerFunc(gAnimationSpeed, Timer, 0); // 70 milliseconds is about 24 fps
    } else {
        if (gLoopMode == 1) {  // if we are in Loop Mode, start over at Frame 0
            gCurrentFrame = 0;
            glutPostRedisplay();
            glutTimerFunc(gAnimationSpeed, Timer, 0);
        } else {
            gPlaybackMode = 0; // we reached the end not in playback mode, so stop
            glutPostRedisplay();
        }
    }
}

/* Interpolate to figure out the in-between keyframes, from laskKey
 * to the frame before currentKey */
void cubicInterpolate(Keyframe &lastKey, Keyframe &currentKey) {
    int t0 = lastKey.frameNumber;
    int t1 = currentKey.frameNumber;
    //std::cout << "T0: " << t0 << " T1: " << t1 << std::endl;

    Vector3 T0 = lastKey.translation;
    Vector3 T1 = currentKey.translation;
    Vector4 R0 = lastKey.rotation;
    Vector4 R1 = currentKey.rotation;
    Vector3 S0 = lastKey.scaleFactor;
    Vector3 S1 = currentKey.scaleFactor;

    for (int i = t0; i < t1; i++) {
        Keyframe newKeyframe;

        double u = (i - t0) / float((t1 - t0));

        //k(u) = k(0)×(2u3-3u2+1) + k(1)×(3u2-2u3)  use Cubic Interpolation
        double k0 = (2 * u * u * u) - (3 * u * u) + 1;
        double k1 = (3 * u * u) - (2 * u * u * u);
        //std::cout << "U: " << u << " " << k0 << " " << k1 << std::endl;

        newKeyframe.frameNumber = i; // create frame i
        newKeyframe.numberKeyframes = gNumberOfFrames;

        // interpolate to create the in-between frames!
        double tx = (T0.x * k0) + (T1.x * k1);
        double ty = (T0.y * k0) + (T1.y * k1);
        double tz = (T0.z * k0) + (T1.z * k1);
        newKeyframe.translation.x = tx;
        newKeyframe.translation.y = ty;
        newKeyframe.translation.z = tz;
            
        double rx = (R0.x * k0) + (R1.x * k1);
        double ry = (R0.y * k0) + (R1.y * k1);
        double rz = (R0.z * k0) + (R1.z * k1);
        double rw = (R0.w * k0) + (R1.w * k1);
        newKeyframe.rotation.x = rx;
        newKeyframe.rotation.y = ry;
        newKeyframe.rotation.z = rz;
        newKeyframe.rotation.w = rw;

        double sx = (S0.x * k0) + (S1.x * k1);
        double sy = (S0.y * k0) + (S1.y * k1);
        double sz = (S0.z * k0) + (S1.z * k1);
        newKeyframe.scaleFactor.x = sx;
        newKeyframe.scaleFactor.y = sy;
        newKeyframe.scaleFactor.z = sz;

        gKeyframes.push_back(newKeyframe);
    }
}

/* Generate all in-between frames, and push them all to gKeyframes vector */
void generateFrames(vector<Keyframe> &keyframes) {

    // see if we have to do some modifications at beginning/end.
    Keyframe firstKeyframe = keyframes[0];
    Keyframe lastKeyframe = keyframes[keyframes.size() - 1];

    // if we don't start at frame 0, we need a starting point at a neutral position.
    if (firstKeyframe.frameNumber != 0) {
        Keyframe frame0;

        frame0.translation.x = 0; // set up a neutral first frame
        frame0.translation.y = 0;
        frame0.translation.z = 0;
        frame0.rotation.x = 0;
        frame0.rotation.y = 0;
        frame0.rotation.z = 0;
        frame0.rotation.w = 0;
        frame0.scaleFactor.x = 1;
        frame0.scaleFactor.y = 1;
        frame0.scaleFactor.z = 1;

        frame0.frameNumber = 0;
        frame0.numberKeyframes = gNumberOfFrames;

        Keyframe frame1 = keyframes[0];
        cubicInterpolate(frame0, frame1);
    }

    // loop through and interpolate between each pair of frames
    for (size_t i = 1; i < keyframes.size(); i++) {
        Keyframe lastKey = keyframes[i-1];
        Keyframe currentKey = keyframes[i];
        cubicInterpolate(lastKey, currentKey);
    } 

    // if we don't have a frame at the end, do cubic interpolation 
    // back to a neutral position.
    if (lastKeyframe.frameNumber != gNumberOfFrames) {
        Keyframe lastFrame;

        lastFrame.translation.x = 0; // set up a neutral last frame
        lastFrame.translation.y = 0;
        lastFrame.translation.z = 0;
        lastFrame.rotation.x = 0;
        lastFrame.rotation.y = 0;
        lastFrame.rotation.z = 0;
        lastFrame.rotation.w = 0;
        lastFrame.scaleFactor.x = 1;
        lastFrame.scaleFactor.y = 1;
        lastFrame.scaleFactor.z = 1;

        lastFrame.frameNumber = gNumberOfFrames + 0; // this is the last frame
        lastFrame.numberKeyframes = gNumberOfFrames;

        Keyframe previousFrame = keyframes[keyframes.size() - 1];
        cubicInterpolate(previousFrame, lastFrame);

        Keyframe frameEnd;
        frameEnd.translation.x = 0; // add 1 more neutral frame
        frameEnd.translation.y = 0;
        frameEnd.translation.z = 0;
        frameEnd.rotation.x = 0;
        frameEnd.rotation.y = 0;
        frameEnd.rotation.z = 0;
        frameEnd.rotation.w = 0;
        frameEnd.scaleFactor.x = 1;
        frameEnd.scaleFactor.y = 1;
        frameEnd.scaleFactor.z = 1;

        frameEnd.frameNumber = gNumberOfFrames;
        frameEnd.numberKeyframes = gNumberOfFrames;
        gKeyframes.push_back(frameEnd);
    } else {
        // we have a last frame. just push it onto the end.
        Keyframe lastKey = keyframes[keyframes.size() - 1];
        gKeyframes.push_back(lastKey);
    }

}

/*
 * GLUT calls this function when any key is pressed while our window has
 * focus.  Here, we just quit if any appropriate key is pressed.  You can
 * do a lot more cool stuff with this here.
 */
void keyfunc(GLubyte key, GLint x, GLint y)
{
    if (gUserInput) {
        if (isdigit(key)) {
            gInputString += key;
        }
        if (key == 13) { // pressed Enter, done entering number
            int toFrame = atoi(gInputString.c_str());
            if (toFrame >= 0 && toFrame <= gNumberOfFrames) {
                std::cout << "Jumping to frame " << toFrame << "!" << std::endl;
                gCurrentFrame = toFrame;
                gUserInput = 0;  // reset, we are done entering input
                gInputString = "";
                glutPostRedisplay();
            } else {
                std::cout << "Frame " << toFrame << " out of range: [" << 0 << ", " << gNumberOfFrames << "]!" << std::endl;
                std::cout << "(Press J to try to enter another frame to jump to)" << std::endl; 
                gUserInput = 0;  // just reset if out of range
                gInputString = "";
            }
        }
    }
    if (key == 'f' || key == 'F') {
        if (gCurrentFrame < gNumberOfFrames) {
            gCurrentFrame += 1;
        } else {
            std::cout << "Already at the last frame!" << std::endl;
        }
        glutPostRedisplay();
    } else if (key == 'r' || key =='R') {
        if (gCurrentFrame > 0) {
            gCurrentFrame -= 1;
        } else {
            std::cout << "Already at first frame!" << std::endl;
        }
        glutPostRedisplay();
    } else if (key == 'j' || key == 'J') {
        std::cout << "Please enter a frame to jump to (and then hit enter): " << std::endl;
        gUserInput = 1;  // enter user input mode
    } else if (key == 'l' || key == 'L') {
        if (gLoopMode == 0) { // toggle loop mode
            gLoopMode = 1;
        } else {
            gLoopMode = 0;
        }
        glutPostRedisplay();
    } else if (key == 'p' || key == 'P') {
        if (gPlaybackMode == 0) {
            gPlaybackMode = 1; // enter playback mode, and start the Timer;
            Timer(0);
        }
    } else if (key == 's' || key == 'S') {
        gPlaybackMode = 0; // end playback mode
        glutPostRedisplay();
    } else if (key == '0' && !gUserInput) {
        gCurrentFrame = 0;
        glutPostRedisplay();
    } else if (key == 'w') {
        if (drawingType == 1) {
            drawingType = 0; // toggle axes on/off
        } else {
            drawingType = 1;
        }
        glutPostRedisplay();
    } else if (key == 27 || key == 'q' || key =='Q') {
        exit(0); // escape or q or Q to exit the program
    } else if (key == 'z' || key == 'Z') {
        if (gAnimationSpeed > 10) {
            gAnimationSpeed -= 10;
        }
    } else if (key == 'x' || key || 'X') {
        gAnimationSpeed += 10;
    }
}

/*
 * GLUT calls this function when any special key is pressed while our window has
 * focus.
 */
void specialfunc(int key, int x, int y)
{
    switch (key)
    {
        case 100: // left arrow
            gTheta += 10;
            break;
        case 102: // right arrow
            gTheta -= 10;
            break;
        case 103:  // down arrow
            gCameraDistance += 0.5; // move camera further
            break;
        case 101:   // up arrow
            gCameraDistance -= 0.5;  // move camera closer

            if (gCameraDistance < 2.0) {
                gCameraDistance = 2.0;  // clamp
            }
            break;
    }
    glutPostRedisplay();
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

// Prints the given matrix
// Assumes column-major format, as in OpenGL
void printMatrix(GLdouble thematrix[16])
{
   for (int i=0; i<4; ++i)     // i = row
   {
      for (int j=0; j<4; ++j)  // j = column
      {
         cout << fixed << setprecision(4) << setw(7)
               << thematrix[j*4+i] << " ";
      }
      cout << endl;
   }
}

/** Utility functions **/

/**
 * Set up OpenGL state.  This does everything so when we draw we only need to
 * actually draw the sphere, and OpenGL remembers all of our other settings.
 */
void initGL()
{
    // Tell openGL to use gouraud shading:
    glShadeModel(GL_SMOOTH);
    drawingType = 1;  // start at Gouraud setting
    
    // Enable back-face culling:
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Enable depth-buffer test.
    glEnable(GL_DEPTH_TEST);
    
    // Set up projection and modelview matrices ("camera" settings) 
    // Look up these functions to see what they're doing.
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // this is the only operation we are doing on GL_PROJECTION matrix
    glFrustum(-10, 10, -10, 10, 1, 100);

    glMatrixMode(GL_MODELVIEW);

    // set light parameters
    glDisable(GL_LIGHTING); // we won't be using lighting, since we have no lights

    // initialize the "quadric" used by GLU to render high-level objects.
    gQuad = gluNewQuadric();
    gluQuadricOrientation(gQuad, GLU_OUTSIDE);
}

/**
 * Main entrance point, obviously.
 * Sets up some stuff then passes control to glutMainLoop() which never
 * returns.
 */
int main(int argc, char* argv[])
{

    if (argc != 2) {
        std::cerr << "USAGE: keyframe script-file-name" << std::endl;
        exit(1);
    }

    int xRes = 400;
    int yRes = 400;

    assert(xRes >= 0);
    assert(yRes >= 0);

    fstream keyframeFile;  // send the script-file-name to the parser
    keyframeFile.open(argv[1], ios::out | ios::in );

    vector<Keyframe> &keyframes = parse_test(keyframeFile);

    gNumberOfFrames = keyframes[1].numberKeyframes - 1; // [0, numFrames - 1]
    if (gNumberOfFrames > 0) {
        gCurrentFrame = 0; // we will start at frame 0!
    }
    
    double max_x = 0;
    double max_y = 0;
    double max_z = 0;
    for (size_t i = 0; i < keyframes.size(); i++) {
        Keyframe keyframe = keyframes[i];
        Vector3 T = keyframe.translation;
        if (abs(T.x) > max_x) {
            max_x = abs(T.x);
        }
        if (abs(T.y) > max_y) {
            max_y = abs(T.y);
        }
        if (T.z > max_z) { // only care about positive z's
            max_z = T.z;
        }
    }

    if (max_z > 2.0) {
        gCameraDistance = max_z + 1;  // make sure we can view entire z range of animation
    }

    generateFrames(keyframes);

    /*
    for (size_t i = 0; i < gKeyframes.size(); i++) {
        Keyframe keyframe = gKeyframes[i];
        std::cout << "TOTAL: " << keyframe.numberKeyframes << std::endl;
        std::cout << "Frame: " << keyframe.frameNumber << std::endl;
        Vector3 T = keyframe.translation;
        std::cout << "T: " << T.x << " " << T.y << " " << T.z << std::endl;
        Vector4 R = keyframe.rotation;
        std::cout << "R: " << R.x << " " << R.y << " " << R.z << " " << R.w << std::endl;
        Vector3 S = keyframe.scaleFactor;
        std::cout << "S: " << S.x << " " << S.y << " " << S.z << std::endl;
    }
    */

    // OpenGL will take out any arguments intended for its use here.
    // Useful ones are -display and -gldebug.
    glutInit(&argc, argv);

    // Get a double-buffered, depth-buffer-enabled window, with an
    // alpha channel.
    // These options aren't really necessary but are here for examples.
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutInitWindowSize(xRes, yRes);
    glutInitWindowPosition(300, 100);

    glutCreateWindow("CS171 HW7");
    
    initGL();

    // set up GLUT callbacks.
    glutDisplayFunc(redraw);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyfunc);
    glutSpecialFunc(specialfunc); // special keyboard functions

    // From here on, GLUT has control,
    glutMainLoop();

    // so we should never get to this point.
    return 1;
}

