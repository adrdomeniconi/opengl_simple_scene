#pragma once

#include <vector>
#include <GL/glew.h>
#include <array>

#include "MeshObject.h"
#include "Line.h"
#include "ShaderLine.h"

class NormalsVisualizer
{
public:

    NormalsVisualizer(MeshObject* meshObject);

    void Render(ShaderLine* shaderLine);

    ~NormalsVisualizer();

private:
    MeshObject* _meshObject;
    std::vector<Line*> _normalLines;

};