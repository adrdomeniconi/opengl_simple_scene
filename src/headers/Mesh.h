#include <GL/glew.h>

class Mesh
{
public:
    Mesh();

void CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numberOfIndices);
void UnbindAll();
void configureVerticesAttribute(unsigned int index, unsigned int vertexAttributesLength, GLfloat *vertices, int VERTEX_LENGTH, unsigned int offset);
void RenderMesh();
void ClearMesh();

~Mesh();

private:
    GLuint VAO, VBO, IBO;
    GLsizei indexCount;
};