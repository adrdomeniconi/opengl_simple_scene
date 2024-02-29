#include "NormalsVisualizer.h"

NormalsVisualizer::NormalsVisualizer(MeshObject &meshObject) : _meshObject(meshObject)
{
    Mesh* mesh = meshObject.GetMesh();

    std::vector<std::array<GLfloat, 3>> verticesPos = mesh->GetVerticesPos();
    std::vector<std::array<GLfloat, 3>> normals = mesh->GetNormals();

    for(size_t i = 0 ; i < normals.size() ; i++)
    {
        std::array<GLfloat, 6> normalsData = {
            verticesPos[i][0],
            verticesPos[i][1],
            verticesPos[i][2],
            verticesPos[i][0] + normals[i][0],
            verticesPos[i][1] + normals[i][1],
            verticesPos[i][2] + normals[i][2]
        };

        Line *line = new Line();
        line->Create(normalsData.data(), 2);
        _normalLines.push_back(line);
    }
}

void NormalsVisualizer::Render(ShaderLine *shaderLine)
{
    shaderLine->UseShader();

    glm::mat4 model(1.0f);
    model = glm::translate(model, _meshObject.Translation());
    model = glm::rotate(model, _meshObject.Rotation().x, glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::rotate(model, _meshObject.Rotation().y, glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::rotate(model, _meshObject.Rotation().z, glm::vec3(0.0f, 0.0f, 1.0f));
    model = glm::scale(model, _meshObject.Scale());

    glUniformMatrix4fv(shaderLine->GetModelLocation(), 1, GL_FALSE, glm::value_ptr(model));

    for(Line *normal : _normalLines)
    {
        normal->Render();
    }
}

NormalsVisualizer::~NormalsVisualizer()
{
}