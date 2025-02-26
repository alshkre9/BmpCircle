#include <stdlib.h>

#include "bmp.h"

struct BMPHEADER *create_bmpheader(int *offset, int size)
{
    struct BMPHEADER *bmpheader = malloc(sizeof(struct BMPHEADER));
    if(bmpheader == NULL)
        return NULL;

    bmpheader->Magic_Numbers[0] = 0x42;
    bmpheader->Magic_Numbers[1] = 0x4D;

    bmpheader->Size = size;
    bmpheader->Reversed1 = 0;
    bmpheader->Reversed2 = 0;
    bmpheader->Offset = 0;

    *offset = 14;

    return bmpheader;
}

struct BITMAPINFOHEADER *create_dibinfoheader(int *offset)
{
    struct BITMAPINFOHEADER *dibheader = malloc(sizeof(struct BITMAPINFOHEADER));
    if(dibheader == NULL)
        return NULL;

    // 40 -> BITMAPINFOHEADER 
    dibheader->Size = 40;

    dibheader->Width = 1024;
    dibheader->Height = 1024;
    dibheader->Planes = 1;
    dibheader->BitCount = RGB;
    dibheader->Compression = BI_RGB;
    dibheader->SizeImage = 0;
    dibheader->XPelsPerMeter = 72;
    dibheader->YPelsPerMeter = 72;
    dibheader->ClrUsed = 0;
    dibheader->ClrImportant = 0;

    *offset = 54;
    return dibheader;
}