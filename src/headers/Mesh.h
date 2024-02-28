#pragma once

#include <GL/glew.h>
#include <vector>

class Mesh
{
public:
    Mesh();

void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int vertexDataCount, unsigned int indexCount, unsigned int vertexLength, unsigned int normalsOffset);
void UnbindAll();
void RenderMesh();
void ClearMesh();

std::vector<GLfloat> GetNormals();

~Mesh();

private:
    GLuint VAO, VBO, IBO;
    GLsizei _indexCount;
    GLsizei _vertexDataCount;
    GLsizei _vertexLength;
    GLsizei _normalsOffset;

    void configureVerticesAttribute(unsigned int index, unsigned int vertexAttributesLength, GLfloat *vertices, int VERTEX_LENGTH, unsigned int offset);
};