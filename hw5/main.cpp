#include <iostream>
#include <cassert>
#include <vector>
#include <iomanip>
#include <string>
#include <sstream>
#include <cmath>
#include <stdlib.h>

#ifdef __APPLE__
#include "OpenGL/gl.h"
#include "OpenGl/glu.h"
#include "GLUT/glut.h"
#else
#include "GL/gl.h"
#include "GL/glu.h"
#include "GL/glut.h"
#endif

#include "matrix.h"
#include "spline.h"
#include "vec3.h"

using namespace std;

int lastX, lastY;
int xRes = 400;
int yRes = 400;
int dragControlPoint = -1;
int displayControlLine = 1;
std::string fileName = "";
Spline gSpline;

// given a value of the pixel that we clicked on, return the value in
// object space (which is on a scale from -1 to 1). 
float getNDCCoord(int pixel, int min, int max, int resolution) 
{

    float smallScale = max - min;
    float result = smallScale * (pixel - resolution/smallScale) / resolution;

    //std::cout << "getNDCCoord " << result << std::endl;
    return result;
}
 
/* Handler for window-repaint event. Call back when the window first appears and
   whenever the window needs to be re-painted. */
void display() 
{
    //std::cout << "Display!" << std::endl;
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)


    if (displayControlLine == 1) {
        const vector<Vec3> &controls = gSpline.getControls();

        glColor3f (1,1,1);
        glBegin(GL_LINE_STRIP);
        for (size_t i = 0; i < controls.size(); i++) {
            glVertex2f(controls[i].x, controls[i].y);
        }
        glEnd();

        glColor3f(1,0,0);
        glPointSize(5);
        glBegin(GL_POINTS);
        for(size_t i=0;i < controls.size();++i) {  // draw control points red!
            glVertex2f(controls[i].x, controls[i].y);
        }
        glEnd();

        //gSpline.printControls();   // for debugging
        //gSpline.printKnots();
    }

    std::vector<Vec3> splinePoints = gSpline.getPoints();
    glColor3f(1,1,0);
    glBegin(GL_LINE_STRIP);
    
    for (int i = 0; i < splinePoints.size(); i++) {
        Vec3 output = splinePoints[i];
        //std::cout << "P1: " << output.x  << " " << output.y << std::endl;
        glVertex2f(output.x, output.y);
    }
    
    
    glEnd();

    glFlush();  // Render now
}

/**
 * GLUT calls this function when the window is resized.
 * All we do here is change the OpenGL viewport so it will always draw in the
 * largest square that can fit in our window..
 */
void resize(GLint w, GLint h)
{
    // Reset the current viewport and perspective transformation
    glViewport(0, 0, w, h);

    xRes = w;  // update so we know the size of the box
    yRes = h;
    gSpline.generatePoints(xRes, yRes);
    //std::cout << "RESIZE" << " "<< w << " " << h << std::endl;

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
    if (key == 'w') {
        if (displayControlLine == 0) {  // toggle control polyline on or off
            displayControlLine = 1;
        } else {
            displayControlLine = 0;
        }
        glutPostRedisplay();    
    } else if (key == 'r') {
        gSpline.reset();
        gSpline.generatePoints(xRes, yRes);
        glutPostRedisplay();
    } else if (key == 's') { // save the data if we were given a file
        if (fileName != "") {
            gSpline.saveSplineData(fileName);
            std::cout << "Saved spline data to "<< fileName << "!"<< std::endl;
        }
    } else if (key == 27 || key == 'q' || key =='Q') {
        exit(0); // escape or q or Q to exit the program
    }
}

static void mouseButton(int button, int state, int x, int y) 
{
    if (state == GLUT_DOWN && displayControlLine == 0) {
        std::cout << "Can't edit while control polyline is toggled off!" << std::endl;
        std::cout << "(press w to toggle control line back on)" << std::endl;
        std::cout << " " << std::endl;
        return;
    }
    switch(button) {
        case GLUT_LEFT_BUTTON:
            if (state == GLUT_DOWN) {
                lastX = x;  // note where the drag began
                lastY = y;
                //std::cout << "Mouse Press:  " << "X: " << x << "  Y: " << y << std::endl;
                double nx = getNDCCoord(x, -1, 1, xRes);
                double ny = getNDCCoord(yRes - y, -1,1, yRes);
                //std::cout << "TRANS: " << nx << " " << ny << std::endl;
                dragControlPoint = gSpline.findControl(nx, ny);
                if (dragControlPoint == -1) {
                    std::cout << "Try clicking on a control point (in red) to drag!" << std::endl;
                    std::cout << "(you may need to click on the upper half of the point)" << std::endl;
                    std::cout << "" << std::endl;
                }

            } else if (state == GLUT_UP) {
                dragControlPoint = -1;
            }
            break;
        case GLUT_MIDDLE_BUTTON:
            // don't do anything for middle button
            break;
        case GLUT_RIGHT_BUTTON:
            if(state == GLUT_DOWN) {
                lastX = x;
                lastY = y; 

                double percentage = -1;
                std::vector<Vec3> pointsWindow = gSpline.getPointsWindowSpace();
                for (size_t i = 0; i < pointsWindow.size(); i++) {
                    Vec3 point = pointsWindow[i];
                    //std::cout << "POINT: " << point.x << " " << point.y << std::endl;
                    if (abs(x - point.x) <= 3 && abs(yRes - y- point.y) <= 3) {
                        //std::cout << "FOUND: " << i << std::endl;
                        //std::cout << "coords: " << point.x << " " << point.y << std::endl;
                        percentage = i / 400.0;
                        break;
                    }
                    if (i == pointsWindow.size() - 1) {
                        std::cout << "Try Control-Clicking on a point on the curve to add a knot!" << std::endl;
                        std::cout << "" << std::endl;
                    }
                }
                //std::cout << "RIGHT CLICK: " << x << "" << y << std::endl;
                if (percentage >= 0) {
                    int positionIndex = gSpline.insertKnot(percentage);
                    gSpline.updateControl(positionIndex);
                    gSpline.generatePoints(xRes, yRes);
                }

                glutPostRedisplay();
            } else if (state == GLUT_UP) {
            }
            break;
    }
}   

static void motion(int x, int y) 
{
    double dy = y - lastY;
    double dx = x - lastX;
    lastX = x;
    lastY = y;

    if (dragControlPoint >= 0) {
        //std::cout << "DRAG" << dx << dy << std::endl;
        double deltaX = dx * 2 / xRes; // multiply by 2/400 to convert to NDC: (1 - (-1)) / xRes
        double deltaY = -dy * 2 / yRes; // in NDC, negative because Y is inverted
        gSpline.moveControl(dragControlPoint, deltaX, deltaY);
        gSpline.generatePoints(xRes, yRes);
        glutPostRedisplay();

    }
}    
 
/* Main function: GLUT runs as a console application starting at main()  */
int main(int argc, char** argv) 
{
    if ((argc != 1) && (argc != 3) && (argc != 4)) {
        std::cerr << "USAGE: editSpline [<xRes> <yRes> [<spline file>]] " << std::endl;
        exit(1);
    }

    xRes = 400;
    yRes = 400;
    if ((argc == 3) || (argc == 4)) {
        xRes = atoi(argv[1]);  // update size if we are given xRes and yRes as inputs
        yRes = atoi(argv[2]);
        assert(xRes >= 0);
        assert(yRes >= 0);
        if (argc == 4) {
            // if we are provided an input file, load data from there
            fileName = argv[3];
            gSpline.loadSplineData(fileName);
            gSpline.generatePoints(xRes, yRes);
        }
    }

    glutInit(&argc, argv);                 // Initialize GLUT

    glutInitWindowSize(xRes, yRes);
    glutInitWindowPosition(300, 100);

    glutCreateWindow("CS171 HW5");

    // set up GLUT callbacks.
    glutDisplayFunc(display); // Register display callback handler for window re-paint
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyfunc);

    glutMouseFunc(mouseButton);
    glutMotionFunc(motion);
    glutMainLoop();           // Enter the event-processing loop
    return 0;
}
