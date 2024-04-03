#pragma once

#include <string>
#include <GL/glew.h>
#include "stb_image.h"

class Texture
{
public:
    Texture();
    Texture(std::string fileLoc);

    bool LoadTexture();
    bool LoadTextureAlpha();
    void UseTexture();
    void ClearTexture();

    ~Texture();

private:
    GLuint textureID;
    int width, height, bitDepth;

    std::string fileLocation;
};