#pragma once

#include <GLM/glm.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "Mesh.h"
#include "ShaderMesh.h"
#include "Material.h"
#include "Texture.h"
#include "Transform.h"

class MeshObject
{
public:

    MeshObject(Mesh *mesh, ShaderMesh *shader, Material material, Texture* texture);

    void Translate(GLfloat x, GLfloat y, GLfloat z);
    void Rotate(GLfloat x, GLfloat y, GLfloat z);
    void Scale(GLfloat x, GLfloat y, GLfloat z);

    glm::vec3 Translation();
    glm::vec3 Rotation();
    glm::vec3 Scale();

    void Render();

    Mesh* GetMesh();

    ~MeshObject();

private:
    Transform _transform;
    Mesh* _mesh;
    ShaderMesh* _shader;
    Material _material;
    Texture* _texture;
};