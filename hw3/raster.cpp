#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "raster.h"

// helper function for DrawTriangle to calculate barycentric coordinates
static double _BarycentricCoordF(double x1, double y1, double x2,
                                 double y2, double x, double y) {
  return (y1 - y2) * x + (x2 - x1) * y + x1 * y2 - x2 * y1;
}

// Draws a triangle, calling DrawPixel (with the given parameter) for every
// pixel drawn. DrawPixel receives both the image coordinates and barycentric
// coordinates of the pixel.
void DrawTriangle(int x0, int y0, int x1, int y1, int x2, int y2, int w, int h,
    void (*DrawPixel)(int, int, double, double, double, void*), void* param) {

  // find the bounding box
  int xMin = x0, xMax = x0, yMin = y0, yMax = y0;
  if (xMin > x1) xMin = x1;
  if (xMin > x2) xMin = x2;
  if (xMax < x1) xMax = x1;
  if (xMax < x2) xMax = x2;
  if (yMin > y1) yMin = y1;
  if (yMin > y2) yMin = y2;
  if (yMax < y1) yMax = y1;
  if (yMax < y2) yMax = y2;
  if (xMin < 0) xMin = 0;
  if (xMax > w) xMax = w;
  if (yMin < 0) yMin = 0;
  if (yMax > h) yMax = h;

  // normalizing values for the barycentric coordinates
  double fAlpha = _BarycentricCoordF(x1, y1, x2, y2, x0, y0),
         fBeta = _BarycentricCoordF(x2, y2, x0, y0, x1, y1),
         fGamma = _BarycentricCoordF(x0, y0, x1, y1, x2, y2);

	// check for zero denominators. if found, these indicate a degenerate
	// triangle which should not be drawn, so just return.
	if (((fAlpha < 1.0E-6) && (fAlpha > -1.0E-6)) ||
      ((fBeta < 1.0E-6) && (fBeta > -1.0E-6)) ||
      ((fGamma < 1.0E-6) && (fGamma > -1.0E-6)))
		return;

  // go over every pixel in the bounding box
  int x, y;
  for (y = yMin; y < yMax; y++) {
    for (x = xMin; x < xMax; x++) {
      // calculate the pixel's barycentric coordinates
      double alpha = _BarycentricCoordF(x1, y1, x2, y2, x, y) / fAlpha;
      double beta = _BarycentricCoordF(x2, y2, x0, y0, x, y) / fBeta;
      double gamma = _BarycentricCoordF(x0, y0, x1, y1, x, y) / fGamma;

      // if the coordinates are nonnegative, draw the pixel
      if (alpha >= 0 && beta >= 0 && gamma >= 0)
        DrawPixel(x, y, alpha, beta, gamma, param);
    }
  }
}
