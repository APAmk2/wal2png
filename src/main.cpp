// main.cpp : Main logic of converter
// 2024 APAMk2 (c)

#include <filesystem>
#include <fstream>
#include <vector>
#include <iostream>
#include "pcx.h"
#include "lodepng.h"
#include "wal.h"

using namespace std;

std::vector<ucolor> palette;

void SetupPalette()
{
    ByteReader* reader = new ByteReader;
    if (!reader->Reset("colormap.pcx", ByteReader::BigEndian)) return;
    pcx_t* file = new pcx_t(reader);
    reader->Close();
    delete reader;

    for (size_t i = 0; i < 256; i++)
    {
        palette.push_back(file->paletteColors[i]);
    }

    palette[255] = ucolor{ 0xff, 0xff, 0xff };	// 255 is transparent
    delete file;
}

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        return -1;
    }
    SetupPalette();

    std::filesystem::path filename = argv[1];
    ByteReader* reader = new ByteReader;
    if (!reader->Reset(filename.string(), ByteReader::BigEndian)) return -1;
    wal_t* file = new wal_t(reader);
    reader->Close();
    delete reader;

    std::vector<unsigned char> image;
    int len = (file->width * file->height) * 4;
    image.resize(len);
    for (size_t i = 0; i < len; i++)
    {
        image[i * 4] = palette[file->pixels[i]].r;     //Red
        image[i * 4 + 1] = palette[file->pixels[i]].g; //Green
        image[i * 4 + 2] = palette[file->pixels[i]].b; //Blue
        image[i * 4 + 3] = 255;                        //Alpha
    }

    std::filesystem::path path = filename;
    path.replace_extension(".png");
    unsigned error = lodepng::encode(std::filesystem::canonical(path).string(), image, file->width, file->height);
    if (error) std::cout << "encoder error " << error << ": " << lodepng_error_text(error) << std::endl;
    
    delete file;
    image.resize(0);
    palette.resize(0);
	return 0;
}
