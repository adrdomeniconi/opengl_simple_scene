#include "MeshObject.h"

MeshObject::MeshObject(Mesh *mesh, ShaderMesh *shader, Material material, Texture *texture) : 
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

void MeshObject::Render()
{     
    _shader->UseShader();
    _transform.Apply(_shader->GetModelLocation());

    // glm::mat4 model(1.0f);
    // glUniformMatrix4fv(_shader->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));

    _material.Use(_shader->GetSpecularIntensityLocation(), _shader->GetSpecularShininessLocation());
    _texture->UseTexture();
    
    _mesh -> RenderMesh();
}

MeshObject::~MeshObject()
{
}
