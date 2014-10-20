#include "spline.h"

#include <cassert>
#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>

using namespace std;

Spline::Spline()
{
    initOriginalData();
}

double
Spline::CoxDeBoor(double u, int i, int k) 
{
    if(k==1)
    {
        if( mKnots[i] <= u && u <= mKnots[i+1] ) {
            return 1.0f;
        }
        return 0.0f;
    }
    double Den1 = mKnots[i+k-1] - mKnots[i];
    double Den2 = mKnots[i+k] - mKnots[i+1];
    double Eq1=0,Eq2=0;
    if(Den1>0) {
        Eq1 = ((u-mKnots[i]) / Den1) * CoxDeBoor(u, i, k-1);
    }
    if(Den2>0) {
        Eq2 = (mKnots[i+k]-u) / Den2 * CoxDeBoor(u, i+1, k-1);
    }
    return Eq1+Eq2;
}

Vec3
Spline::evalSpline(double t)
{
    Vec3 output(0, 0, 0);

    int numControls = (int)(mControls.size());
    for(int k = 0;k < numControls; k++) {

        // calculate the effect of this point on the curve
        double val = CoxDeBoor(t, k, 4);  // u, i, k, Knot
        //std::cout << "T: " << t << " K: "<< k << " Val: " << Val << std::endl;

        if(val>0.001f) {

            // sum effect of CV on this part of the curve
            output.x += val * mControls[k].x;
            output.y += val * mControls[k].y;
            output.z += val * mControls[k].z;
            //OutControls[1] += val * mControls[i][1];
            //OutControls[2] += val * mControls[i][2];
        }
    }
    return output;
}

double
Spline::getCoefficient(int i, int j)
{
    if (i <= (j - 4)) {
        return 1.0;
    } else if (i >= j + 1) {
        return 0.0;
    } else {
        double num = mKnots[j] - mKnots[i];
        double den = mKnots[i + 4] - mKnots[i];
        if (den > 0) {
            return num/den;
        } else {
            return 0.0;
        }
    }
}

// inserts a knot into the knot vector at value t;
int
Spline::insertKnot(double t) 
{
    std::vector<double>::iterator it;

    int positionCounter = -1;
    for (it=mKnots.begin(); it<mKnots.end(); it++) {
        positionCounter += 1;
        if (*it > t) {  // this is where we will insert the knot
            //std::cout << *it << std::endl;
            mKnots.insert ( it , t );
            break;
        }
    }

    // just to print out our knot vector
    //printKnots();

    return positionCounter;
}

void
Spline::addControl(Vec3 &aControls)
{
    mControls.push_back(aControls);
}

void
Spline::deleteLastControl()
{
    mControls.pop_back();
}

Vec3
Spline::getControl(size_t i) const
{
    assert(i < mControls.size());
    return mControls[i];
}

void
Spline::setControl(size_t i, Vec3 &aControls)
{
    assert(i < mControls.size());
    mControls[i] = aControls;
} 

void
Spline::moveControl(size_t i, double dx, double dy)
{
    assert(i < mControls.size());
    mControls[i].x += dx;
    mControls[i].y += dy;
}

int
Spline::findControl(double x, double y)
{
    double tolerance = .02;
    for (size_t i = 0; i < mControls.size(); i++) {
        Vec3 p = mControls[i];
        if (abs(x - p.x) <= tolerance && abs(y - p.y) <= tolerance) {
            //std::cout << "FOUND: " << i << std::endl;
            return i;
        }
    }
    return -1;
}

// update the control list after knot insertion at the jth position 
// in gKnots
void
Spline::updateControl(size_t aIndex) 
{
    vector<Vec3> newControls;
    newControls.push_back(mControls[0]); // the first point doesn't change
    for (size_t i = 1; i < mControls.size(); i++) {
        Vec3 pI = mControls[i];
        Vec3 pIPrev = mControls[i-1];
        double a = getCoefficient(i, aIndex);
        //std::cout << "I: " << i << "  A: " << a << std::endl;
        //std::cout << "POINT I: " << pI.x << " " << pI.y << std::endl;
        //std::cout << "POINT I-1: " << pIPrev.x << " " << pIPrev.y << std::endl;
        Vec3 newControl(0,0,0);
        newControl.x += (1-a) * pIPrev.x;
        newControl.y += (1-a) * pIPrev.y;

        newControl.x += (a) * pI.x;
        newControl.y += (a) * pI.y;

        //std::cout << "RES: " << newControl.x << " " << newControl.y << std::endl;

        newControls.push_back(newControl);
    }
    Vec3 lastControls = mControls[mControls.size() - 1];
    newControls.push_back(lastControls);

    mControls = newControls;
}

void 
Spline::generatePoints(int xRes, int yRes) {
    mSplinePoints.clear();
    mSplinePointsWindow.clear();
    for(int j=0;j<=399;j++) {

        double t  = j / 399.0;
        //std::cout << "T: " << t << " J: "<< j << std::endl;
        Vec3 output = evalSpline(t);

        //float valuePerPixel = (value - min) / (max - min);

        /* note that we really want to map from 0 to (resolution - 1), which
        is the maximum size of our array */
        //float pixel = (output.x - (-1)) / (1 - (-1)) * (xRes - 1);
        Vec3 outputWindow((output.x - (-1)) / (1 - (-1)) * (xRes - 1), 
                          (output.y - (-1)) / (1 - (-1)) * (yRes - 1),
                          0);
        mSplinePoints.push_back(output);  // keep track of 400 points of clickability
        mSplinePointsWindow.push_back(outputWindow);
    }
}

void
Spline::saveSplineData(std::string fileName) {
    ofstream myfile;
    myfile.open(fileName);
    for(size_t i=0;i < mControls.size();++i) {  // print control points
        myfile << mControls[i].x << " " << mControls[i].y << "\n";
    }
    myfile << "Knots Vector:\n";   // seperator  between controls and knots
    for(size_t i=0;i < mKnots.size();++i) {  // print control points
        myfile << mKnots[i] << " ";
    }
    myfile << "\n";
    myfile.close();
}
void
Spline::loadSplineData(std::string fileName) {

    ifstream infile(fileName.c_str());

    if (!infile) {  // if the file doesn't exist, just start at original U shape
        return;
    }

    mControls.clear();
    mKnots.clear();
    std::string a;
    std::string b;
    //infile.open(fileName);
    while (infile >> a >> b) {
        if (a == "Knots" && b == "Vector:") { // we hit the seperator
            break;
        }
        Vec3 point(atof(a.c_str()), atof(b.c_str()), 0);
        mControls.push_back(point);
    }
    // now, parse the knot vector
    while (infile >> a) {
        mKnots.push_back(atof(a.c_str()));
    }

    infile.close();
}

void
Spline::reset()
{
    initOriginalData();
}

void
Spline::initOriginalData()
{
    mControls.clear();
    Vec3 point1(-0.75, 0.75,0);
    Vec3 point2(-0.75, -0.75,0);
    Vec3 point3(0.75, -0.75,0);
    Vec3 point4(0.75, 0.75,0);
    mControls.push_back(point1);
    mControls.push_back(point2);
    mControls.push_back(point3);
    mControls.push_back(point4);

    // construct initial Knot Vector:
    mKnots.clear();
    mKnots.push_back(0);
    mKnots.push_back(0);
    mKnots.push_back(0);
    mKnots.push_back(0);
    mKnots.push_back(1);
    mKnots.push_back(1);
    mKnots.push_back(1);
    mKnots.push_back(1);
}

void
Spline::printControls()
{
    std::cout << "CONTROL POINTS: " << std::endl;
    for(size_t i=0;i < mControls.size();++i) {  // print control points
        std::cout << mControls[i].x << " " << mControls[i].y << std::endl;
    }
}

void
Spline::printKnots()
{
    std::cout << "KNOTS: " << std::endl;
    for(size_t i=0;i < mKnots.size();++i) {  // print control points
        std::cout << mKnots[i] << " ";
    }
    std::cout << std::endl;
}
