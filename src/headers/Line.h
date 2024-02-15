#include <GL/glew.h>

class Line
{
public:
    Line();

void Create(GLfloat *vertices, unsigned int numOfVertices);
void UnbindAll();
void Render();
void Clear();

~Line();

private:
    GLuint VAO, VBO;

    void configureVerticesAttribute(unsigned int index, unsigned int vertexAttributesLength, GLfloat *vertices, int VERTEX_LENGTH, unsigned int offset);
};