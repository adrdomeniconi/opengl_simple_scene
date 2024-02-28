#pragma once

#include <vector>
#include <GL/glew.h>

#include "Mesh.h"

class NormalsVisualizer
{
public:

    NormalsVisualizer(Mesh *mesh);
    ~NormalsVisualizer();

private:
    std::vector<GLfloat> _normals;
};