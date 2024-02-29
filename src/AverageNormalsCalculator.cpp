#include "AverageNormalsCalculator.h"

AverageNormalsCalculator::AverageNormalsCalculator()
{
}

void AverageNormalsCalculator::Calculate(unsigned int *indices, unsigned int indicesCount, GLfloat *vertices, unsigned int verticesCount, unsigned int verticesLength, unsigned int normalOffset)
{
    //For each verex the normals are calculated as the average of the triangles of the surfaces that the vertex is part.
    for(size_t i = 0; i < indicesCount; i += 3)
    {
        unsigned int vertice0Idx = indices[i] * verticesLength;
        unsigned int vertice1Idx = indices[i+1] * verticesLength;
        unsigned int vertice2Idx = indices[i+2] * verticesLength;

        glm::vec3 vertice0_pos(vertices[vertice0Idx], vertices[vertice0Idx + 1], vertices[vertice0Idx + 2]);
        glm::vec3 vertice1Pos(vertices[vertice1Idx], vertices[vertice1Idx + 1], vertices[vertice1Idx + 2]);
        glm::vec3 vertice2Pos(vertices[vertice2Idx], vertices[vertice2Idx + 1], vertices[vertice2Idx + 2]);

        glm::vec3 edge1 = vertice1Pos - vertice0_pos;
        glm::vec3 edge2 = vertice2Pos - vertice0_pos;

        glm::vec3 normal = glm::cross(edge1, edge2);
        normal = glm::normalize(normal);

        accumulateVerticeNormal(vertices, vertice0Idx, normal, normalOffset);
        accumulateVerticeNormal(vertices, vertice1Idx, normal, normalOffset);
        accumulateVerticeNormal(vertices, vertice2Idx, normal, normalOffset);
    }

    normalizeVerticesNormals(vertices, verticesCount, verticesLength, normalOffset);
}

void AverageNormalsCalculator::accumulateVerticeNormal(GLfloat *vertices, unsigned int verticeIdx, glm::vec3 normal, unsigned int normalOffset)
{
    unsigned int verticeNormalsIdx = verticeIdx + normalOffset;
    vertices[verticeNormalsIdx] += normal.x;
    vertices[verticeNormalsIdx + 1] += normal.y;
    vertices[verticeNormalsIdx + 2] += normal.z;
}

void AverageNormalsCalculator::updateVerticeNormal(GLfloat *vertices, unsigned int verticeIdx, glm::vec3 normal, unsigned int normalOffset)
{
    unsigned int verticeNormalsIdx = verticeIdx + normalOffset;
    vertices[verticeNormalsIdx] = normal.x;
    vertices[verticeNormalsIdx + 1] = normal.y;
    vertices[verticeNormalsIdx + 2] = normal.z;
}

void AverageNormalsCalculator::normalizeVerticesNormals(GLfloat *vertices, unsigned int verticesCount, unsigned int verticesLength, unsigned int normalOffset)
{
    for(size_t i = 0; i < verticesCount/verticesLength; i++)
    {
        unsigned int verticeNormalsIdx = i * verticesLength + normalOffset;

        glm::vec3 normal(vertices[verticeNormalsIdx], vertices[verticeNormalsIdx + 1], vertices[verticeNormalsIdx + 2]);
        normal = glm::normalize(normal);

        updateVerticeNormal(vertices, i * verticesLength, normal, normalOffset);
    }
}

AverageNormalsCalculator::~AverageNormalsCalculator()
{
}

