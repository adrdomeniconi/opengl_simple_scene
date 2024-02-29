#include "NormalsVisualizer.h"

NormalsVisualizer::NormalsVisualizer(Mesh *mesh) : _mesh(mesh)
{
    //Do nothing
}

void NormalsVisualizer::Render()
{
}

NormalsVisualizer::~NormalsVisualizer()
{
}

// std::vector<std::array<GLfloat, 3>> Mesh::GetNormals()
// {
//     const unsigned int verticesCount = _vertexDataCount/_vertexLength;
//     std::vector<std::array<GLfloat, 3>> normals;

//     // std::cout << "Start getting normals: " << std::endl;
//     for(int i = 0; i < verticesCount; i ++)
//     {
//         int baseIdx = i * _vertexLength;
//         std::array<GLfloat, 3> normalVertices = {
//             _vertices[baseIdx] + _vertices[baseIdx + _normalsOffset],
//             _vertices[baseIdx + 1] + _vertices[baseIdx + 1 + _normalsOffset],
//             _vertices[baseIdx + 2] + _vertices[baseIdx + 2 + _normalsOffset]
//         };

//         normals.push_back(normalVertices);
//     }

//     return normals;
// }