#include <string>
#include <vector>

using namespace std;

struct Point {
	double x;
	double y;
};

struct Polyline {
    vector<Point> points;
};

struct Pixel {
	short r;
	short g;
	short b;
};

struct Image {
	int width;
	int height;
	Pixel** canvas;
};
