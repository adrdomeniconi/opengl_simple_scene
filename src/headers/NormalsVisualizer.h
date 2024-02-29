#pragma once

#include <vector>
#include <GL/glew.h>

#include "MeshObject.h"
#include "Line.h"
#include "ShaderLine.h"

class NormalsVisualizer
{
public:

    NormalsVisualizer(MeshObject *meshObject);

    void Render(ShaderLine *shaderLine, glm::mat4 projection, glm::mat4 cameraViewMatrix);

    ~NormalsVisualizer();

private:
    MeshObject* _meshObject;
    std::vector<Line*> _normalLines;

};