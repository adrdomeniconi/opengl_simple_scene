#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <fstream>

#include <GL/glew.h>

class Shader
{
public:
    Shader();

    GLuint CreateFromString(const char* vertexCode, const char* fragmentCode);
    GLuint CreateFromFiles(const char* vertexLocation, const char* fragmentLocation);

    std::string ReadFile(const char* fileLocation); 

    void UseShader();
    void ClearShader();

    ~Shader();

private:
    GLuint shaderID;
    GLuint CompileShader(const char* vertexCode, const char* fragmentCode);
    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType);
};