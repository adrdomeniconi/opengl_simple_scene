#include "Object.h"

Object::Object(Mesh *mesh, Shader *shader, Material material, Texture texture) : _mesh(mesh), _shader(shader), _material(material), _texture(texture)
{
    //Do nothing
}

void Object::Render()
{     
    // _mesh->UseShader();

//     model = glm::mat4(1.0f);     
//     model = glm::translate(model, glm::vec3(0.0f, .3, -1.5f));
//     model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

//     glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
//     dullMaterial.Use(uniformSpecularIntensity, uniformSpecularShininess);
//     dirtTexture.UseTexture();

//     meshList[1] -> RenderMesh();
}

Object::~Object()
{
}
