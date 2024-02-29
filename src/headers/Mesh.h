#pragma once

#include <GL/glew.h>
#include <vector>
#include <iostream>
#include <memory>


class Mesh
{
public:
    Mesh();

void CreateMesh(GLfloat *verticesData, unsigned int *indices, unsigned int vertexDataCount, unsigned int indexCount, unsigned int vertexLength, unsigned int normalsOffset);
void UnbindAll();
void RenderMesh();
void ClearMesh();

std::vector<std::array<GLfloat, 3>> GetNormals();
std::vector<std::array<GLfloat, 3>> GetVerticesPos();

~Mesh();

private:
    GLuint VAO, VBO, IBO;
    std::unique_ptr<GLfloat[]> _verticesData;
    GLsizei _indexCount;
    GLsizei _vertexDataCount;
    GLsizei _vertexLength;
    GLsizei _normalsOffset;

    void configureVerticesAttribute(unsigned int index, unsigned int vertexAttributesLength, GLfloat *vertices, int VERTEX_LENGTH, unsigned int offset);
};