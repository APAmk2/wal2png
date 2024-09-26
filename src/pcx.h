// pcx.h : PCX Reader header
// 2024 APAMk2 (c)

#pragma once

#include <string>
#include <vector>
#include "ByteReader.hpp"

struct ucolor
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
};

class pcx_t
{
public:
    uint8_t manufacturer = 0x0a;
    uint8_t version = 5;
    uint8_t encoding = 1;
    uint8_t bits_per_pixel = 8;
    uint16_t xmin = 0;
    uint16_t ymin = 0;
    uint16_t xmax = 640;
    uint16_t ymax = 480;
    uint16_t hres = 640;
    uint16_t vres = 480;
    std::vector<uint8_t> palette; //[48];
    uint8_t color_planes = 1;
    uint16_t bytes_per_line = 256;
    uint16_t palette_type = 0;
    std::vector<uint8_t> filler; //[58];
    std::vector<uint8_t> pixels;
    std::vector<ucolor> paletteColors;

    pcx_t(ByteReader* reader);
};