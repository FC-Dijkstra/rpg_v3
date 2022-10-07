#pragma once
#include <string>

class Texture2D
{
public:
    unsigned int id;
    unsigned int width;
    unsigned int height;
    unsigned int internalFormat;
    unsigned int imageFormat;
    unsigned int wrapS;
    unsigned int wrapT;
    unsigned int filterMin;
    unsigned int filterMax;

    Texture2D();

    void generate(unsigned int width, unsigned int height, unsigned int components, unsigned char* data);
    void bind() const;
    void unbind() const;
    void load(const char* textureFilePath);
};