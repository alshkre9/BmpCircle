#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "bmp.h"
#include "helper.h"

enum BACKGROUNDS {BLACK = 01};

char *BACKGROUNDS[] = {
    "black", /* black background */
};


enum SHAPES {CIRCLE = 01, RECTANGLE = 02};

char *SHAPES[] = {
    "circle",
    "rectangle"
};

char *filename = "output.bmp";

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("usage: ./program <background> <shape>\n");
        return 1;
    }

    int background;
    if(!(background = inarray(BACKGROUNDS, sizeof(BACKGROUNDS) / sizeof(char *), *++argv)))
    {
        printf("%s is not supported\n", *argv);
        return 2;
    }

    int shape;
    if(!(shape = inarray(SHAPES, sizeof(SHAPES) / sizeof(char *), *++argv)))
    {
        printf("%s is not supported\n", *argv);
        return 2;
    }

    int offset = 0;

    struct BITMAPINFOHEADER *dibheader = create_dibinfoheader(&offset);
    
    int holder = (dibheader->Width * (RGB/8) % 4);
    int padding = !holder ? 0 : 4 - holder;

    struct BMPHEADER *bmpheader = create_bmpheader(&offset, (dibheader->Height * dibheader->Width * (RGB/8)) + 54 + dibheader->Height * padding);
    
    /* 2D pixels table*/
    struct RGB24 pixels[dibheader->Height][dibheader->Width];

    switch (background)
    {
    case BLACK:
        black(dibheader->Width, dibheader->Height, pixels);
        break;
    default:
        break;
    }

    switch (shape)
    {
    case CIRCLE:
        draw_circle(dibheader->Width, dibheader->Height, pixels);
        break;
    case RECTANGLE:
        draw_rectangle(dibheader->Width, dibheader->Height, pixels);
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

    uint8_t dummy[3];

    for(int row = 0; row < dibheader->Height; row++)
    {
        for(int column = 0; column < dibheader->Width; column++)
        {
            fwrite(&pixels[row][column].Blue, sizeof(pixels[row][column].Blue), 1,image);
            fwrite(&pixels[row][column].Green, sizeof(pixels[row][column].Green), 1,image);
            fwrite(&pixels[row][column].Red, sizeof(pixels[row][column].Red), 1,image);
            
            // add padding
            if ((column + 1 == dibheader->Width))
                fwrite(dummy, 1, padding, image);
        }
    }

    free(bmpheader);
    free(dibheader);

    fclose(image);

    exit(0);
}

