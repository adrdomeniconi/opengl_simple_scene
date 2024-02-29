#include "MaterialLibrary.h"

MaterialLibrary::MaterialLibrary()
{
    materials[MaterialType::Dull] = Material(0.3f, 4);
    materials[MaterialType::Shiny] = Material(4.0f, 256);
}

Material MaterialLibrary::GetMaterial(MaterialType type)
{
    return materials.at(type);
}

MaterialLibrary::~MaterialLibrary()
{
}
