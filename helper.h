#ifndef HELPER
#define HELPER

#include <stdint.h>
#include <stdbool.h>

uint32_t swap_endian(uint32_t val);

bool inarray(char *array[], int len, char *s);

char *getexte(char *filename);

#endif