#include "MeshObject.h"

MeshObject::MeshObject(Mesh *mesh, ShaderMesh *shader, Material material, Texture texture) : _mesh(mesh), _shader(shader), _material(material), _texture(texture)
{
    //Do nothing
}

void MeshObject::Render()
{     
    _shader->UseShader();

//     model = glm::mat4(1.0f);     
//     model = glm::translate(model, glm::vec3(0.0f, .3, -1.5f));
//     model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
    // glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

    // _material.Use(_shader->GetSpecularIntensityLocation(), _shader->GetSpecularShininessLocation());
    // dirtTexture.UseTexture();

//     meshList[1] -> RenderMesh();
}

MeshObject::~MeshObject()
{
}
