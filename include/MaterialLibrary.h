#pragma once

#include <map>

#include "Material.h"

class MaterialLibrary
{

public:
    enum class MaterialType
    {
        Dull,
        Shiny
    };

    MaterialLibrary();

    Material GetMaterial(MaterialType type);
    
    ~MaterialLibrary();

private:
    std::map<MaterialType, Material> _materials;
};