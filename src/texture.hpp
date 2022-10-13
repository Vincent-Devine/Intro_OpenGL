#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include "iostream"

#include "gl.hpp"

#pragma pack(push, 1)
struct BMPHeader
{
    char signature[2];
    unsigned int fileSize;
    char reserved1[2];
    char reserved2[2];
    unsigned int fileOffsetToPixelArray;
};

struct DIBHeader
{
    unsigned int unused_00;
    unsigned int width;
    unsigned int height;
    unsigned short unused_01;
    unsigned short bpp; // bits per pixel (24,32)
};
#pragma pack(pop)

namespace texture
{
    extern GLuint idWall;

    unsigned char* loadFile(const char* _filename, size_t* _fileSizeOut);
    unsigned char* loadBMP24(const char* _filename, int* _widthOut, int* _heightOut);
    
    GLuint LoadTexture(const char* _filename);
    void Delete();
}