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

    MeshObject(std::unique_ptr<MeshRenderer> meshRenderer, ShaderMesh *shader, Material material, Texture* texture);
    MeshObject(std::unique_ptr<MeshRenderer> meshRenderer, ShaderMesh *shader, Material material, Texture* texture, const glm::mat4 parentMatrix);

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
    std::unique_ptr<MeshRenderer> _meshRenderer;
    ShaderMesh* _shader;
    Material _material;
    Texture* _texture;
    const glm::mat4 _parentMatrix;
};