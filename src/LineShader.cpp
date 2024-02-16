#include "LineShader.h"

LineShader::LineShader(const char *vertexShaderLocation, const char *fragmentShaderLocation): uniformModel(0), uniformProjection(0), shader(Shader())
{
    GLuint shaderID = shader.CreateFromFiles(vertexShaderLocation, fragmentShaderLocation);
    std::cout << "Shader program created: " << shaderID << std::endl;
    if(shaderID == 0)
    {
        throw std::runtime_error("Error creating shader.");
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
}

GLuint LineShader::GetProjectionLocation() { return uniformProjection; }

GLuint LineShader::GetModelLocation() { return uniformModel; }

GLuint LineShader::GetViewLocation() { return uniformView; }

void LineShader::UseShader()
{
    shader.UseShader();
}

void LineShader::ClearShader()
{
    shader.ClearShader();
    uniformModel = 0;
    uniformProjection = 0;
}

LineShader::~LineShader()
{
    ClearShader();
}
