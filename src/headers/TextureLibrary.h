#pragma once

#include <map>
#include <iostream>

#include "Texture.h"

class TextureLibrary 
{
public:
    enum class TextureType {
        Brick,
        Dirt,
        Floor
    };

    TextureLibrary();
    Texture* GetTexture(TextureType type);

    ~TextureLibrary();


private:
    std::map<TextureType, Texture*> _textures;
};