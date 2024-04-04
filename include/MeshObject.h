#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "MeshRenderer.h"
#include "ShaderMesh.h"
#include "Material.h"
#include "Texture.h"
#include "Transform.h"
#include "TextureLibrary.h"

class MeshObject
{
public:

    MeshObject(MeshRenderer *mesh, ShaderMesh *shader, Material material, Texture* texture);

    void Translate(GLfloat x, GLfloat y, GLfloat z);
    void Rotate(GLfloat x, GLfloat y, GLfloat z);
    void Scale(GLfloat x, GLfloat y, GLfloat z);

    glm::vec3 Translation();
    glm::vec3 Rotation();
    glm::vec3 Scale();

    void Render();

    MeshRenderer* GetMesh();

    ~MeshObject();

private:
    Transform _transform;
    MeshRenderer* _mesh;
    ShaderMesh* _shader;
    Material _material;
    Texture* _texture;
};