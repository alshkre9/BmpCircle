#ifndef FILTERS
#define FILTERS

#include "bmp.h"

void black(int width, int height, struct RGB24 pixels[width][height]);
void draw_circle(int width, int height, struct RGB24 pixels[width][height]);
void draw_rectangle(int width, int height, struct RGB24 pixels[width][height]);

int inarray(char *array[], int len, char *s);
char *getexte(char *filename);

#endif