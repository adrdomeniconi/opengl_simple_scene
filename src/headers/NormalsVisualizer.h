#pragma once

#include <vector>
#include <GL/glew.h>

#include "Mesh.h"

class NormalsVisualizer
{
public:

    NormalsVisualizer(Mesh *mesh);

    void Render();

    ~NormalsVisualizer();

private:
    Mesh* _mesh;
};