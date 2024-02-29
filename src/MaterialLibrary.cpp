#include "MaterialLibrary.h"

MaterialLibrary::MaterialLibrary()
{
    _materials[MaterialType::Dull] = Material(0.3f, 4);
    _materials[MaterialType::Shiny] = Material(4.0f, 256);
}

Material MaterialLibrary::GetMaterial(MaterialType type)
{
    return _materials.at(type);
}

MaterialLibrary::~MaterialLibrary()
{
}
