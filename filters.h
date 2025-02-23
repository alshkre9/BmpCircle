#ifndef FILTERS
#define FILTERS

#include <stdint.h>
#include <stdbool.h>


struct PIXEL getpixel(char *);
char *getexte(char *);
bool inarray(char *[], int , char *);
uint32_t swap_endian(uint32_t val);

char *filters[] = {
    "grayscale"
};

#endif