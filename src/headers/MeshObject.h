#pragma once

#include <GLM/glm.hpp>

#include "Mesh.h"
#include "ShaderMesh.h"
#include "Material.h"
#include "Texture.h"
// #include "Transform.h"

class MeshObject
{
public:

    MeshObject(Mesh *mesh, ShaderMesh *shader, Material material, Texture texture);

    void Render();

    ~MeshObject();

private:
    Mesh* _mesh;
    Shader* _shader;
    Material _material;
    Texture _texture;
};