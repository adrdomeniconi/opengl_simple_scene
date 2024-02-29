#include "TextureLibrary.h"

TextureLibrary::TextureLibrary()
{
    textures[TextureType::Brick] = new Texture("../textures/brick.png");
    textures[TextureType::Dirt] = new Texture("../textures/dirt.png");
    textures[TextureType::Floor] = new Texture("../textures/plain.png");

    //TODO: Can be improved to load only the textures that will be used
    for (auto texturePair : textures) {
        std::cout << static_cast<int>(texturePair.first) << ": " << texturePair.second << std::endl;
        texturePair.second->LoadTexture();
    }
}

Texture* TextureLibrary::GetTexture(TextureType type)
{
    return textures.at(type);
}

TextureLibrary::~TextureLibrary()
{
    for (auto texturePair : textures) {
        delete(texturePair.second);
    }
}
