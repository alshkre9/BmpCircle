#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "helper.h"


uint32_t swap_endian(uint32_t val) {
    return 
        ((val >> 24) & 0xFF) | 
        ((val >> 8) & 0xFF00) | 
        ((val << 8) & 0xFF0000) | 
        ((val << 24) & 0xFF000000);
}

bool inarray(char *array[], int len, char *s)
{
    for(int i = 0; i < len; i++)
        if(!strcmp(array[i], s))
            return true;

    return false;
}

char *getexte(char *filename)
{
    while(*filename != '.' && *filename != '\0') filename++;

    return filename;
}