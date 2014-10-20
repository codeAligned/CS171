#include <iostream>
#include <list>
#include <vector>
#include <cassert>
#include "stdlib.h"
#include "data.h"
#include "matrix.h"

using namespace std;

vector<Polyline> &parse_test(istream &datafile);

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
    if (argc != 7) {
        std::cout << "USAGE: draw2d [xmin] [xmax] [ymin] [ymax] [xRes] [yRes]" << std::endl;
        exit(1);
    }

    double xmin = atof(argv[1]);
    double xmax = atof(argv[2]);
    double ymin = atof(argv[3]);
    double ymax = atof(argv[4]);
    double xRes = atof(argv[5]);
    double yRes = atof(argv[6]);

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
    

    vector<Polyline> &polylines = parse_test(cin);

    for (size_t i = 0; i < polylines.size(); i++) {
        Polyline line = polylines[i];
        vector<Point> linePoints = line.points;
        for (size_t j = 1; j < linePoints.size(); j++) {
            int x1 = getPixel(linePoints[j-1].x, xmin, xmax, xRes);
            int y1 = getPixel(linePoints[j-1].y, ymin, ymax, yRes);
            int x2 = getPixel(linePoints[j].x, xmin, xmax, xRes);
            int y2 = getPixel(linePoints[j].y, ymin, ymax, yRes);
            Bresenham(x1, y1, x2, y2, false, &image);
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
