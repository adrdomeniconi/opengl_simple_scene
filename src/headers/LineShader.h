#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdexcept> 

#include <GL/glew.h>

#include "Shader.h"

class LineShader
{
public:
    LineShader(const char* vertexShaderLocation, const char* fragmentShaderLocation);

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();

    void UseShader();
    void ClearShader();

    ~LineShader();

private:
    Shader shader;
    GLuint uniformProjection, uniformModel, uniformView;
};