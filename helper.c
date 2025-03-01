#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "bmp.h"
#include "helper.h"


void draw_circle(int width, int height, struct RGB24 pixels[width][height])
{
    int radius = 100;
    int x_origin = (width/2); 
    int y_origin = (height/2);

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            double range = sqrt((x - x_origin)*(x - x_origin) + (y - y_origin)*(y - y_origin));
            if (range <= radius + 2 && range >= radius - 2)
            {
                pixels[y][x].Red = ~pixels[y][x].Red;
                pixels[y][x].Green = ~pixels[y][x].Green;  
                pixels[y][x].Blue = ~pixels[y][x].Blue;
            }
        }
    }
}

void draw_rectangle(int width, int height, struct RGB24 pixels[width][height])
{
    int length = 100;
    int x_origin = (width/2);
    int y_origin = (height/2);

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if (abs(x - x_origin)  <= length && abs(y - y_origin) <= length && (abs(y - y_origin) >= length - 4 || abs(x - x_origin) >= length - 4))
            {
                pixels[y][x].Red = ~pixels[y][x].Red;
                pixels[y][x].Green = ~pixels[y][x].Green; 
                pixels[y][x].Blue = ~pixels[y][x].Blue;
            }
        }
    }
}

void black(int width, int height, struct RGB24 pixels[width][height])
{
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            uint8_t avg = (pixels[row][column].Red + pixels[row][column].Blue + pixels[row][column].Green) / 3; 
            pixels[row][column].Red = 0x00;
            pixels[row][column].Green = 0x00;
            pixels[row][column].Blue = 0x00;
        }
    }
}

char *lowers(char * string)
{
    char *output = string;
    while(*string)
    {
        *string = tolower(*string);
        *string++;
    }
    return output;
}

int inarray(char *array[], int len, char *s)
{
    int i;
    for(i = 0; i < len; i++)
        if(!strcmp(array[i], lowers(s)))
        return i + 1;
        
    return 0;
}

char *getexte(char *filename)
{
    while(*filename != '.' && *filename != '\0') filename++;

    return filename;
}