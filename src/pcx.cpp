// pcx.cpp : PCX Reader logic
// 2024 APAMk2 (c)

#include "pcx.h"
#include <stdint.h>

pcx_t::pcx_t(ByteReader* reader)
{
    manufacturer = reader->u8();
    version = reader->u8();
    encoding = reader->u8();
    bits_per_pixel = reader->u8();
    xmin = reader->u16(); 
    ymin = reader->u16();
    xmax = reader->u16();
    ymax = reader->u16();

    if (manufacturer != 0x0a ||
        version != 5 ||
        encoding != 1 ||
        bits_per_pixel != 8 ||
        xmax >= 640 ||
        ymax >= 480)
    {
        printf("ERROR: BAD PCX FILE\n");
        return;
    }

    hres = reader->u16();
    vres = reader->u16();
    for (size_t i = 0; i < 48; i++)
    {
        palette.push_back(reader->u8());
    }
    reader->u8();
    color_planes = reader->u8();
    bytes_per_line = reader->u16();
    palette_type = reader->u16();
    for (size_t i = 0; i < 58; i++)
    {
        filler.push_back(reader->u8());
    }

    int x, y;
    int runLength;

    for (y = 0; y <= ymax; y++)
    {
        for (x = 0; x <= xmax; )
        {
            uint8_t dataByte = reader->u8();

            if ((dataByte & 0xC0) == 0xC0)
            {
                runLength = dataByte & 0x3F;
                dataByte = reader->u8();
            }
            else
                runLength = 1;

            while (runLength-- > 0)
            {
                pixels.push_back(dataByte);
                x++;
            }
        }
    }

    reader->Pos(reader->Bytes() - 768);
    for (size_t i = 0; i < 256; i++)
    {
        ucolor currColor;
        currColor.r = reader->u8();
        currColor.g = reader->u8();
        currColor.b = reader->u8();

        paletteColors.push_back(currColor);
    }
}