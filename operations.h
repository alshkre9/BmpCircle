#ifndef FILTERS
#define FILTERS

#include "bmp.h"

void grayscale(int width, int height, struct RGB24 pixels[width][height]);
void blue(int width, int height, struct RGB24 pixels[width][height]);

#endif