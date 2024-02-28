#include "ShaderLine.h"

ShaderLine::ShaderLine(const char *vertexShaderLocation, const char *fragmentShaderLocation): 
    Shader(),
    uniformModel(0), 
    uniformProjection(0)
{
    GLuint shaderID = CreateFromFiles(vertexShaderLocation, fragmentShaderLocation);
    std::cout << "Shader program created: " << shaderID << std::endl;
    
    if(shaderID == 0)
    {
        throw std::runtime_error("Error creating shader.");
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
}

GLuint ShaderLine::GetProjectionLocation() { return uniformProjection; }

GLuint ShaderLine::GetModelLocation() { return uniformModel; }

GLuint ShaderLine::GetViewLocation() { return uniformView; }

ShaderLine::~ShaderLine()
{
    ClearShader();
}
