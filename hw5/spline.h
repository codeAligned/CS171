#ifndef __SPLINE__
#define __SPLINE__

#include <vector>
#include "vec3.h"

using namespace std;

class Spline {

public:
    Spline();

    Vec3 evalSpline(double t);

    // inserts a knot into the knot vector at value t
    // return position index of new knot
    int insertKnot(double t);

    double getCoefficient(int i, int j);
    void addControl(Vec3 &aControl);
    void deleteLastControl();
    Vec3 getControl(size_t i) const;
    void setControl(size_t i, Vec3 &aControl);
    void setControls(vector<Vec3> &aControls) { mControls = aControls; }
    void moveControl(size_t i, double dx, double dy);

    // return index if found, -1 if not found
    int findControl(double dx, double dy);

    // update the control list after knot insertion at the jth position 
    // in mKnots
    void updateControl(size_t index);

    const vector<Vec3> &getControls() { return mControls; };
    const vector<double> &getKnots() { return mKnots; };

    void generatePoints(int xRes, int yRes);
    const vector<Vec3> &getPoints() { return mSplinePoints; };
    const vector<Vec3> &getPointsWindowSpace() { return mSplinePointsWindow; };

    void saveSplineData(std::string fileName);
    void loadSplineData(std::string fileName);

    // debug
    void printControls();
    void printKnots();

    void reset();
private:
    double CoxDeBoor(double u, int i, int k);
    void initOriginalData();

    std::vector<double> mKnots;
    std::vector<Vec3> mControls;
    std::vector<Vec3> mSplinePoints;
    std::vector<Vec3> mSplinePointsWindow;

};
#endif
