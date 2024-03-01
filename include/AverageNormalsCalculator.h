#pragma once

#include <GL/glew.h>
#include <GLM/glm.hpp>

class AverageNormalsCalculator
{
public:
    AverageNormalsCalculator();

    static void Calculate(unsigned int *indices, unsigned int indicesCount, GLfloat *vertices, unsigned int verticesCount, unsigned int verticesLength, unsigned int normalOffset);

    ~AverageNormalsCalculator();

private:

    static void accumulateVerticeNormal(GLfloat *vertices, unsigned int verticeIdx, glm::vec3 normal, unsigned int normalOffset);
    static void updateVerticeNormal(GLfloat *vertices, unsigned int verticeIdx, glm::vec3 normal, unsigned int normalOffset);
    static void normalizeVerticesNormals(GLfloat *vertices, unsigned int verticesCount, unsigned int verticesLength, unsigned int normalOffset);
};