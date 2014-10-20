#include <string>
#include <vector>

using namespace std;

struct Vector3 {
	double x;
	double y;
	double z;
};

struct Vector4 {
	double x;
	double y;
	double z;
	double w;
};

struct TransformCommand {
    std::string transformation;
    std::vector<double> data;
};

struct Transform {
	vector <TransformCommand> transformations;
}; 

struct Coordinate3 {
	vector <Vector3> points;
}; 

struct IndexedFaceLines {
	vector <double> indices;
}; 

struct IndexedFaceSet {
	vector <IndexedFaceLines> lines;
}; 

struct Point {
	double x;
	double y;
};

struct Polyline {
    vector<Point> points;
};

class CameraBlock {
public:
	Vector3 position;
	Vector4 orientation;
	double nearDistance;
	double farDistance;
	double left;
	double right;
	double top;
	double bottom;
};

class SeparatorBlock {
public:
	vector <Transform> transforms;
	vector <Coordinate3> points;
	vector <IndexedFaceSet> indices;
};

class Block {
public:
	int blockType;
	CameraBlock camera;
	SeparatorBlock separator;
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
