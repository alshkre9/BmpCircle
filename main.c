#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "bmp.h"
#include "filters.h"

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("USAGE: ./Program Image Filter\n");
        return 1;
    }

    FILE *image;
    int offset = 0;
    char *filename = *++argv;

    if(!(image = fopen(filename, "rb")))
    {
        printf("Error: cann't open %s\n", *argv);
        exit(2);
    }

    if(!inarray(filters, sizeof(filters) / sizeof(char *), *++argv))
    {
        printf("%s filter's not supported\n", *argv);
        exit(3);
    }
    
    char *extension = getexte(filename);
    
    struct BMPHEADER *bmpheader = get_bmpheader(image, &offset);
    
    if(!bmpheader)
    {
        printf("%s is not a bmp file", filename);
        exit(4);
    }
    
    struct BITMAPINFOHEADER *dibheader = get_dibheader(image);

    offset = 54;
    
    if(dibheader == NULL)
    {
            printf("Dibheader Is Not BITMAPINFOHEADER");
            exit(5);
    }
    
    size_t RowSize = (dibheader->BitCount * dibheader->Width)/8; 
    size_t ColumnSize = (dibheader->BitCount * dibheader->Height)/8;

    struct RGB24 pixels[dibheader->Height][dibheader->Width];

    for(int row = 0; row < dibheader->Height; row++)
    {
        for(int column = 0; column < dibheader->Width; column++)
        {
            char clr[3];
            fread(clr, 1, 3, image);
            // offset += offset;
            pixels[row][column] = (struct RGB24) {clr[2], clr[1], clr[0]};
        }
    }

    for(int row = 0; row < dibheader->Height; row++)
    {
        for(int column = 0; column < dibheader->Width; column++)
        {
            printf("Red: %x Green: %x Blue: %x\n", pixels[row][column].Red, pixels[row][column].Green, pixels[row][column].Blue);
        }
    }

    fclose(image);
    image = fopen(filename, "r+");

    fseek(image, offset,SEEK_SET);
    for(int row = 0; row < dibheader->Height; row++)
    {
        for(int column = 0; column < dibheader->Width; column++)
        {
            fwrite(&pixels[row][column].Blue, sizeof(pixels[row][column].Blue), 1,image);
            fwrite(&pixels[row][column].Green, sizeof(pixels[row][column].Green), 1,image);
            fwrite(&pixels[row][column].Blue, sizeof(pixels[row][column].Blue), 1,image);
        }
    }

    free(bmpheader);
    free(dibheader);

    fclose(image);

    exit(0);
}



