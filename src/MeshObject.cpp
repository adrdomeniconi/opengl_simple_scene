#include "MeshObject.h"

MeshObject::MeshObject(std::unique_ptr<MeshRenderer> meshRenderer, ShaderMesh *shader, Material material, Texture* texture) :
    _meshRenderer(std::move(meshRenderer)), 
    _shader(shader), 
    _material(material), 
    _texture(texture),
    _transform(Transform()),
    _parentMatrix(glm::mat4(1.0f))
{
    //Do nothing
}

MeshObject::MeshObject(std::unique_ptr<MeshRenderer> meshRenderer, ShaderMesh *shader, Material material, Texture *texture, const glm::mat4 parentMatrix) :
    _meshRenderer(std::move(meshRenderer)), 
    _shader(shader), 
    _material(material), 
    _texture(texture),
    _transform(Transform()),
    _parentMatrix(parentMatrix)
{
    //Do nothing
}

void MeshObject::Translate(GLfloat x, GLfloat y, GLfloat z)
{
    _transform.Translate(x, y, z);
}

void MeshObject::Rotate(GLfloat x, GLfloat y, GLfloat z)
{
    _transform.Rotate(x, y, z);
}

void MeshObject::Scale(GLfloat x, GLfloat y, GLfloat z)
{
    _transform.Scale(x, y, z);
}

glm::vec3 MeshObject::Translation()
{
    return _transform.Translation();
}

glm::vec3 MeshObject::Rotation()
{
    return _transform.Rotation();
}

glm::vec3 MeshObject::Scale()
{
    return _transform.Scale();
}

void MeshObject::Render()
{     
    _shader->UseShader();

    //In the case of having a parent model, the transform should be calculated considering the parent transform.
    _transform.Apply(_shader->GetModelLocation(), _parentMatrix);

    _material.Use(_shader->GetSpecularIntensityLocation(), _shader->GetSpecularShininessLocation());
    
    if(_texture)
    {
        _texture->UseTexture();
    }
    else
    {
        std::cout << "Not applying texture in the MeshObject" << std::endl;
    }

    _meshRenderer -> RenderMesh();
}

MeshRenderer* MeshObject::GetMesh()
{
    return _meshRenderer.get();
}

MeshObject::~MeshObject()
{
}
