#include "texture.hpp"

#include <cassert>
#include <cstring>
#include <fstream>

GLuint texture::idWall = 0.f;

unsigned char* texture::loadFile(const char* _filename, size_t* _fileSizeOut)
{
    unsigned char* data = nullptr;

    // Open file
    std::ifstream file(_filename, std::ios_base::binary);
    if (!file.is_open())
    {
        printf("Error to open file '%s'\n", _filename);
        return nullptr;
    }

    // Read filesize
    file.seekg(0, std::ios_base::end);
    *_fileSizeOut = file.tellg();
    file.seekg(0, std::ios_base::beg);

    // Allocate memory
    data = new unsigned char[*_fileSizeOut];
    file.read((char*)data, *_fileSizeOut);

    file.close();

    return data;
}

unsigned char* texture::loadBMP24(const char* _filename, int* _widthOut, int* _heightOut)
{
    size_t filesize;
    unsigned char* data = loadFile(_filename, &filesize);

    if(data == nullptr)
        return nullptr;

    BMPHeader* header = (BMPHeader*)(data);
    DIBHeader* dibHeader = (DIBHeader*)(data + sizeof(BMPHeader));

    assert(dibHeader->bpp == 24);
    int width = dibHeader->width;
    int height = dibHeader->height;

    unsigned char* pixel = new unsigned char[width * height * 3];
    unsigned char* pixelArray = data + header->fileOffsetToPixelArray;

    memcpy(pixel, pixelArray, width * height * 3);

    if(_widthOut)
        *_widthOut = width;
    if(_heightOut)
        *_heightOut = height;

    delete data;
    return pixel;
}

GLuint texture::LoadTexture(const char* _filename)
{
    GLuint idTexture;
    glGenTextures(1, &idTexture); 
    glBindTexture(GL_TEXTURE_2D, idTexture);

    int width = 0;
    int height = 0;
    unsigned char* texture = loadBMP24(_filename, &width, &height);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glBindTexture(GL_TEXTURE_2D,0);

    delete texture;
    return idTexture;
}

void texture::Delete()
{
    glDeleteTexture(1, &idWall);
}
