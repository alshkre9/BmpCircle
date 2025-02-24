#ifndef BMP
#define BMP

#include <stdio.h>
#include <stdint.h>

struct BMPHEADER *get_bmpheader(FILE *, int *);
struct BITMAPINFOHEADER *get_dibheader(FILE *, int *);

struct BMPHEADER {
    uint8_t Magic_Numbers[2];
    uint32_t Size;
    uint16_t Reversed1;
    uint16_t Reversed2;
    uint32_t Offset;
};

struct BITMAPINFOHEADER {
    uint32_t Size;
    int32_t  Width;
    int32_t  Height;
    
    uint16_t Planes;
    uint16_t BitCount;

    uint32_t Compression;
    uint32_t SizeImage;

    int32_t XPelsPerMeter;
    int32_t YPelsPerMeter;
    
    uint32_t ClrUsed;
    uint32_t ClrImportant;
};

struct RGB24 {
    uint8_t Red;
    uint8_t Green;
    uint8_t Blue;
};

#endif