#include <stdlib.h>

#include "bmp.h"

struct BMPHEADER *get_bmpheader(FILE *image, int *offset)
{
    struct BMPHEADER *bmpheader = malloc(sizeof(struct BMPHEADER));

    fread(bmpheader->MagicNumbers, sizeof(*bmpheader->MagicNumbers), sizeof(bmpheader->MagicNumbers), image);

    if(bmpheader->MagicNumbers[0] != 0x42 || bmpheader->MagicNumbers[1] != 0x4d)
        return NULL;
        
    fread(&(bmpheader->Size), 1, sizeof(bmpheader->Size), image);

    if(!bmpheader->Size)
        return NULL;

    fread(&(bmpheader->Reversed1), 1, sizeof(bmpheader->Reversed1), image);
    fread(&(bmpheader->Reversed2), 1, sizeof(bmpheader->Reversed2), image);

    fread(&(bmpheader->Offset), 1, sizeof(bmpheader->Offset), image);

    *offset = 14;

    return bmpheader;
}

struct BITMAPINFOHEADER *get_dibheader(FILE *image)
{
    struct BITMAPINFOHEADER *dibheader = malloc(sizeof(struct BITMAPINFOHEADER));

    fread(&(dibheader->Size), 1, sizeof(dibheader->Size), image);

    if(dibheader->Size != 40)
        return NULL;

    fread(&(dibheader->Width), 1, sizeof(dibheader->Width), image);
    fread(&(dibheader->Height), 1, sizeof(dibheader->Height), image);

    fread(&(dibheader->Planes), 1, sizeof(dibheader->Planes), image);
    fread(&(dibheader->BitCount), 1, sizeof(dibheader->BitCount), image);

    fread(&(dibheader->Compression), 1, sizeof(dibheader->Compression), image);
    fread(&(dibheader->SizeImage), 1, sizeof(dibheader->SizeImage), image);

    fread(&(dibheader->XPelsPerMeter), 1, sizeof(dibheader->XPelsPerMeter), image);
    fread(&(dibheader->YPelsPerMeter), 1, sizeof(dibheader->YPelsPerMeter), image);

    fread(&(dibheader->ClrUsed), 1, sizeof(dibheader->ClrUsed), image);
    fread(&(dibheader->ClrImportant), 1, sizeof(dibheader->ClrImportant), image);

    return dibheader;
}

// struct RGB getpixel(RGB)
// {
    // struct PIXEL pixel = {colors[2], colors[1], colors[0]};
    // return pixel;
// }