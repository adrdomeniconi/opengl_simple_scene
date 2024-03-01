#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdexcept> 

#include <GL/glew.h>

#include "Shader.h"

class ShaderLine : public Shader
{
public:
    ShaderLine(const char* vertexShaderLocation, const char* fragmentShaderLocation);

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();

    ~ShaderLine();

private:
    GLuint uniformProjection, uniformModel, uniformView;
};