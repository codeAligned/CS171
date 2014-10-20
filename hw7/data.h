#ifndef __DATA_H
#define __DATA_H

#include <string>
#include <vector>
#include "vec3.h"

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
	double z;
};

struct Polyline {
    vector<Point> points;
};

struct Light {
	Vector3 location;
	Vector3 color;
};

struct Material {
	Vector3 ambient;
	Vector3 diffuse;
	Vector3 specular;
	double shininess;
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
	Material material;
	vector <Vector3> normals;
	vector <double> normalIndices;
	string fileName;
	vector <Vector3> textureCoords;
	vector <double> textureIndices;
};

class Block {
public:
	int blockType;
	CameraBlock camera;
	SeparatorBlock separator;
	Light light;
};

class Keyframe {
public:
	int numberKeyframes;
	int frameNumber;
	Vector3 translation;
	Vector4 rotation;
	Vector3 scaleFactor;
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
	double** zBuffer;
};

struct RasterParam {
    int shadingMode;
    Vec3 p1NDC;
    Vec3 p2NDC;
    Vec3 p3NDC;
    Vec3 p1World;
    Vec3 p2World;
    Vec3 p3World;
    Vec3 p1Norm;
    Vec3 p2Norm;
    Vec3 p3Norm;
    Pixel polygonColor;  // 0-255
    Vec3 p1Color; // 0-1
    Vec3 p2Color; // 0-1
    Vec3 p3Color; // 0-1
    Image *image;
};

#endif // __DATA_H
