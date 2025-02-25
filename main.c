#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "bmp.h"
#include "operations.h"

int inarray(char *array[], int len, char *s);
char *getexte(char *filename);

enum FILTERS {BLUE = 1};

char *filename = "output.bmp";

char *operations[] = {
    "blue", /* blue background */
};

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("USAGE: ./Program Operation\n");
        return 1;
    }

    int operation;
    if(!(operation = inarray(operations, sizeof(operations) / sizeof(char *), *++argv)))
    {
        printf("%s operation not supported\n", *argv);
        return 2;
    }
    
    int offset = 0;
    
    struct BMPHEADER *bmpheader = create_bmpheader(&offset, (100 * 100 * 24) + 54);
    
    struct BITMAPINFOHEADER *dibheader = create_dibinfoheader(&offset);

    struct RGB24 pixels[dibheader->Height][dibheader->Width];

    switch (operation)
    {
    case BLUE:
        blue(dibheader->Width, dibheader->Height, pixels);
        break;
    default:
        break;
    }

    /* Create new bmp file */

    FILE *image = fopen(filename, "w"); 
    
    fwrite(bmpheader->Magic_Numbers, sizeof(*bmpheader->Magic_Numbers), sizeof(bmpheader->Magic_Numbers), image);
    fwrite(&(bmpheader->Size), sizeof(bmpheader->Size), 1, image);
    fwrite(&(bmpheader->Reversed1), sizeof(bmpheader->Reversed1), 1, image);
    fwrite(&(bmpheader->Reversed2),sizeof(bmpheader->Reversed2), 1, image);
    fwrite(&(bmpheader->Offset), sizeof(bmpheader->Offset), 1, image);
    fwrite(&(dibheader->Size),sizeof(dibheader->Size), 1, image);
    fwrite(&(dibheader->Width), sizeof(dibheader->Width), 1, image);
    fwrite(&(dibheader->Height), sizeof(dibheader->Height), 1, image);
    fwrite(&(dibheader->Planes), sizeof(dibheader->Planes), 1, image);
    fwrite(&(dibheader->BitCount), sizeof(dibheader->BitCount), 1, image);
    fwrite(&(dibheader->Compression), sizeof(dibheader->Compression), 1, image);
    fwrite(&(dibheader->SizeImage), sizeof(dibheader->SizeImage), 1, image);
    fwrite(&(dibheader->XPelsPerMeter), sizeof(dibheader->XPelsPerMeter), 1, image);
    fwrite(&(dibheader->YPelsPerMeter), sizeof(dibheader->YPelsPerMeter), 1, image);
    fwrite(&(dibheader->ClrUsed), sizeof(dibheader->ClrUsed), 1, image);
    fwrite(&(dibheader->ClrImportant), sizeof(dibheader->ClrImportant), 1, image);

    for(int row = 0; row < dibheader->Height; row++)
    {
        for(int column = 0; column < dibheader->Width; column++)
        {
            fwrite(&pixels[row][column].Blue, sizeof(pixels[row][column].Blue), 1,image);
            fwrite(&pixels[row][column].Green, sizeof(pixels[row][column].Green), 1,image);
            fwrite(&pixels[row][column].Red, sizeof(pixels[row][column].Red), 1,image);
        }
    }


    free(bmpheader);
    free(dibheader);

    fclose(image);

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