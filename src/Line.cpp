#include "Line.h"

Line::Line(): VAO(0), VBO(0) { }

void Line::Create(GLfloat *vertices, unsigned int numOfVertices)
{
    int VERTEX_LENGTH = 3; //x, y, z

    int POS_OFFSET = 0;
    int POS_LENGTH = 3;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);  //Copy the data to the GPU

    configureVerticesAttribute(0, POS_LENGTH, vertices, VERTEX_LENGTH, POS_OFFSET);

    UnbindAll();
}

void Line::UnbindAll()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Line::Render()
{
    glBindVertexArray(VAO);
    glDrawArrays(GL_LINES, 0, 2);
    glBindVertexArray(0);
}

void Line::Clear()
{
    if(VBO != 0)
    {
        glDeleteBuffers(1, &VBO);
        VBO = 0;
    }
    if(VAO != 0)
    {
        glDeleteVertexArrays(1, &VAO);
        VAO = 0;
    }
}

Line::~Line()
{
    Clear();
}

void Line::configureVerticesAttribute(unsigned int index, unsigned int vertexAttributesLength, GLfloat *vertices, int VERTEX_LENGTH, unsigned int offset)
{
    glVertexAttribPointer(index, vertexAttributesLength, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * VERTEX_LENGTH, (void *)(sizeof(vertices[0]) * offset));
    glEnableVertexAttribArray(index);
}
