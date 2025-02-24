#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "bmp.h"
#include "operations.h"

int inarray(char *array[], int len, char *s);
char *getexte(char *filename);

enum FILTERS {GRAYSCALE = 1, BLUE = 2};

char *filters[] = {
    "grayscale",
    "blue"
};

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("USAGE: ./Program Image Filter\n");
        return 1;
    }

    FILE *image;
    char *filename = *++argv;
    
    if(!(image = fopen(filename, "rb")))
    {
        printf("Error: cann't open %s\n", *argv);
        exit(2);
    }
    
    int operation;
    if(!(operation = inarray(filters, sizeof(filters) / sizeof(char *), *++argv)))
    {
        printf("%s operation not supported\n", *argv);
        exit(3);
    }
    
    // char *extension = getexte(filename);
    int offset = 0;

    struct BMPHEADER *bmpheader = get_bmpheader(image, &offset);
    
    if(bmpheader ==  NULL)
    {
        printf("%s is not a bmp file", filename);
        exit(4);
    }
    
    struct BITMAPINFOHEADER *dibheader = get_dibheader(image, &offset);

    if(dibheader == NULL)
    {
            printf("Dibheader Is Not BITMAPINFOHEADER");
            exit(5);
    }
    
    int RowSize = (dibheader->BitCount * dibheader->Width)/8; 
    int ColumnSize = (dibheader->BitCount * dibheader->Height)/8;

    struct RGB24 pixels[dibheader->Height][dibheader->Width];

    for(int row = 0; row < dibheader->Height; row++)
    {
        for(int column = 0; column < dibheader->Width; column++)
        {
            char clr[3];
            fread(clr, 1, 3, image);
            pixels[row][column] = (struct RGB24) {clr[2], clr[1], clr[0]};
        }
    }

    switch (operation)
    {
    case GRAYSCALE:
        grayscale(dibheader->Width, dibheader->Height, pixels);
        break;
    case BLUE:
        blue(dibheader->Width, dibheader->Height, pixels);
        break;
    default:
        break;
    }

    image = fopen(filename, "r+");

    fseek(image, offset, SEEK_SET);
    
    for(int row = 0; row < dibheader->Height; row++)
    {
        for(int column = 0; column < dibheader->Width; column++)
        {
            fwrite(&pixels[row][column].Blue, sizeof(pixels[row][column].Blue), 1,image);
            fwrite(&pixels[row][column].Green, sizeof(pixels[row][column].Green), 1,image);
            fwrite(&pixels[row][column].Red, sizeof(pixels[row][column].Red), 1,image);
        }
    }

    // create new bmp file
    FILE *new_image = fopen("output.bmp", "wb"); 
    
    fwrite(bmpheader->Magic_Numbers, sizeof(*bmpheader->Magic_Numbers), sizeof(bmpheader->Magic_Numbers), new_image);
    fwrite(&(bmpheader->Size), sizeof(bmpheader->Size), 1, new_image);
    fwrite(&(bmpheader->Reversed1), sizeof(bmpheader->Reversed1), 1, new_image);
    fwrite(&(bmpheader->Reversed2),sizeof(bmpheader->Reversed2), 1, new_image);
    fwrite(&(bmpheader->Offset), sizeof(bmpheader->Offset), 1, new_image);
    fwrite(&(dibheader->Size),sizeof(dibheader->Size), 1, new_image);
    fwrite(&(dibheader->Width), sizeof(dibheader->Width), 1, new_image);
    fwrite(&(dibheader->Height), sizeof(dibheader->Height), 1, new_image);
    fwrite(&(dibheader->Planes), sizeof(dibheader->Planes), 1, new_image);
    fwrite(&(dibheader->BitCount), sizeof(dibheader->BitCount), 1, new_image);
    fwrite(&(dibheader->Compression), sizeof(dibheader->Compression), 1, new_image);
    fwrite(&(dibheader->SizeImage), sizeof(dibheader->SizeImage), 1, new_image);
    fwrite(&(dibheader->XPelsPerMeter), sizeof(dibheader->XPelsPerMeter), 1, new_image);
    fwrite(&(dibheader->YPelsPerMeter), sizeof(dibheader->YPelsPerMeter), 1, new_image);
    fwrite(&(dibheader->ClrUsed), sizeof(dibheader->ClrUsed), 1, new_image);
    fwrite(&(dibheader->ClrImportant), sizeof(dibheader->ClrImportant), 1, new_image);

    for(int row = 0; row < dibheader->Height; row++)
    {
        for(int column = 0; column < dibheader->Width; column++)
        {
            fwrite(&pixels[row][column].Blue, sizeof(pixels[row][column].Blue), 1,new_image);
            fwrite(&pixels[row][column].Green, sizeof(pixels[row][column].Green), 1,new_image);
            fwrite(&pixels[row][column].Red, sizeof(pixels[row][column].Red), 1,new_image);
        }
    }


    free(bmpheader);
    free(dibheader);

    fclose(image);
    fclose(new_image);

    exit(0);
}

int inarray(char *array[], int len, char *s)
{
    int i;
    for(i = 0; i < len; i++)
        if(!strcmp(array[i], s))
            return i + 1;

    return 0;
}

char *getexte(char *filename)
{
    while(*filename != '.' && *filename != '\0') filename++;

    return filename;
}