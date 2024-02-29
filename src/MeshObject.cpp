#include "MeshObject.h"

MeshObject::MeshObject(Mesh *mesh, ShaderMesh *shader, Material material, Texture* texture) :
    _mesh(mesh), 
    _shader(shader), 
    _material(material), 
    _texture(texture),
    _transform(Transform())
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
    _transform.Apply(_shader->GetModelLocation());
    _material.Use(_shader->GetSpecularIntensityLocation(), _shader->GetSpecularShininessLocation());
    _texture->UseTexture();
    
    _mesh -> RenderMesh();
}

Mesh *MeshObject::GetMesh()
{
    return _mesh;
}

MeshObject::~MeshObject()
{
}
