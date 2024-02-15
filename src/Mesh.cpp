#include "Mesh.h"

/*
Rendering Workflow Summary
Initialization: When you create a mesh, you generate and bind VAO, VBO, and IBO, upload data, and configure how that data should be interpreted, then unbind them to finalize setup.
During Rendering: Binding the VAO (which indirectly binds the VBO and IBO according to its configuration) sets up the OpenGL state machine with all the necessary information to render that mesh. The draw call (glDrawElements in this case) uses this state to render the mesh.
After Rendering: Unbinding the VAO (and optionally the IBO) ensures that subsequent OpenGL operations do not inadvertently modify or use these objects.
*/

Mesh::Mesh()
{
    // Identifiers provided by OpenGL that will be used subsequently in OpenGL calls to refer to these objects. The relevant configuration and data are stored on the GPU. These IDs are used to bind the corresponding GPU-stored objects to the OpenGL context. When you operate on these IDs (binding, setting data, drawing, etc.), you're instructing OpenGL to use the data and configurations associated with these IDs that are stored in GPU memory.

    // VAO (Vertex Array Object) 
    //Purpose: The VAO stores configurations of vertex attributes (such as positions, texture coordinates, normals, etc.) and which VBOs to use when attributes are specified. It also remembers which IBO (if any) is bound when you bind the VAO. 
    //Data: When you bind a VAO and then set vertex attribute pointers (e.g., with glVertexAttribPointer) and enable them (e.g., with glEnableVertexAttribArray()), the VAO stores this configuration. However, the actual vertex attribute data is stored in the VBOs.
    VAO = 0;

    //VBO (Vertex Buffer Object)
    //Purpose: The VBO is used to store vertex data in GPU memory, including positions, texture coordinates, normals, and any other vertex attribute data.
    //Data: The actual data (floats, integers, etc.) for vertex attributes are stored here. When you bind a VBO and upload data to it using glBufferData, the data is copied to GPU memory.
    VBO = 0;

    //IBO (Index Buffer Object) or EBO (Element Buffer Object)
    //Purpose: The IBO is used to store indices that OpenGL uses to draw the vertices in an order specified by the index array. This allows for more efficient memory usage by reusing vertices.
    //Data: The actual indices (usually unsigned integers) that tell OpenGL how to construct primitives (triangles, lines, etc.) from the vertex data are stored here.
    IBO = 0;

    indexCount = 0;
}

void Mesh::CreateMesh(GLfloat *vertices, unsigned int *indices, unsigned int numOfVertices, unsigned int numOfIndices)
{
    indexCount = numOfIndices;
    
    int VERTEX_LENGTH = 8;

    int POS_OFFSET = 0;
    int POS_LENGTH = 3;

    int TEXTURE_LENGTH = 2;
    int TEXTURE_OFFSET = 3;

    int NORMALS_LENGTH = 3;
    int NORMALS_OFFSET = 5;

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * numOfIndices, indices, GL_STATIC_DRAW); //Copy the data to the GPU

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0]) * numOfVertices, vertices, GL_STATIC_DRAW);  //Copy the data to the GPU
    
    configureVerticesAttribute(0, POS_LENGTH, vertices, VERTEX_LENGTH, POS_OFFSET);
    configureVerticesAttribute(1, TEXTURE_LENGTH, vertices, VERTEX_LENGTH, TEXTURE_OFFSET);
    configureVerticesAttribute(2, NORMALS_LENGTH, vertices, VERTEX_LENGTH, NORMALS_OFFSET);

    UnbindAll();
}

void Mesh::UnbindAll()
{
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void Mesh::configureVerticesAttribute(unsigned int index, unsigned int vertexAttributesLength, GLfloat *vertices, int VERTEX_LENGTH, unsigned int offset)
{
    glVertexAttribPointer(index, vertexAttributesLength, GL_FLOAT, GL_FALSE, sizeof(vertices[0]) * VERTEX_LENGTH, (void *)(sizeof(vertices[0]) * offset));
    glEnableVertexAttribArray(index);
}

void Mesh::RenderMesh()
{
    if(indexCount > 0)
    {
        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}

void Mesh::ClearMesh()
{
    if(IBO != 0)
    {
        glDeleteBuffers(1, &IBO);
        IBO = 0;
    }
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

    indexCount = 0;
}

Mesh::~Mesh()
{
    ClearMesh();
}