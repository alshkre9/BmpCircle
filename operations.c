#include "bmp.h"
#include "operations.h"

void grayscale(int width, int height, struct RGB24 pixels[width][height])
{
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            uint8_t avg = (pixels[row][column].Red + pixels[row][column].Blue + pixels[row][column].Green) / 3; 
            pixels[row][column].Red = avg;
            pixels[row][column].Green = avg;
            pixels[row][column].Blue = avg;
        }
    }
}

void blue(int width, int height, struct RGB24 pixels[width][height])
{
    for(int row = 0; row < height; row++)
    {
        for(int column = 0; column < width; column++)
        {
            uint8_t avg = (pixels[row][column].Red + pixels[row][column].Blue + pixels[row][column].Green) / 3; 
            pixels[row][column].Red = 0x00;
            pixels[row][column].Green = 0x00;
            pixels[row][column].Blue = 0xFF;
        }
    }
}