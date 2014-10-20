#ifndef __RASTER_H
#define __RASTER_H

// Draws a triangle, by calling the supplied DrawPixel function for each pixel
// contained in the triangle. Parameters:
//   x1, y1, x2, y2, x3, y3: coordinates of 3 points defining a triangle in
//     pixel coordinates.
//   w, h: window width & height (can be set to some large number like INT_MAX
//     if you do bounds checking in DrawPixel)
//   DrawPixel: a function to be called to draw a pixel.
//   data: optional data to be passed to DrawPixel function.
// The DrawPixel function is called with these parameters:
//   x, y: the pixel coordinate to be drawn.
//   a, b, g: the barycentric coordinates of the pixel to be drawn.
//   data: the contents of the data parameter to DrawTriangle.
void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int w, int h,
  void (*DrawPixel)(int x, int y, double a, double b, double g, void* data),
  void* data);

#endif // __RASTER_H
