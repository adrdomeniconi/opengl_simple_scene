#pragma once

#include <GLM/glm.hpp>

#include "Mesh.h"
#include "Shader.h"
#include "Material.h"
#include "Texture.h"
// #include "Transform.h"

class Object
{
public:

    Object(Mesh *mesh, Shader *shader, Material material, Texture texture);

    void Render();

    ~Object();

private:
    Mesh* _mesh;
    Shader* _shader;
    Material _material;
    Texture _texture;
};