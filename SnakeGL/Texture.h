#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>
#include "stb_image.h"

class Texture
{
public:

    Texture();

    void LoadTexture(const char* fileName, bool alpha);
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const;

private:
    unsigned int ID, width, height;
    // texture Format
    unsigned int imgFormat, intFormat;
    // texture configuration
    unsigned int wrapS, wrapT, filterMin, filterMax;
};

#endif