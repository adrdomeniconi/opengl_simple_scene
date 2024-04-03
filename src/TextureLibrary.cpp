#include "TextureLibrary.h"

TextureLibrary::TextureLibrary()
{
    _textures[TextureType::Brick] = new Texture("../resources/textures/brick.png");
    _textures[TextureType::Dirt] = new Texture("../resources/textures/dirt.png");
    _textures[TextureType::Floor] = new Texture("../resources/textures/plain.png");

    //TODO: Can be improved to load only the textures that will be used
    for (auto texturePair : _textures) {
        std::cout << static_cast<int>(texturePair.first) << ": " << texturePair.second << std::endl;
        texturePair.second->LoadTextureAlpha();
    }
}

Texture* TextureLibrary::GetTexture(TextureType type)
{
    return _textures.at(type);
}

TextureLibrary::~TextureLibrary()
{
    for (auto texturePair : _textures) {
        delete(texturePair.second);
    }
}
