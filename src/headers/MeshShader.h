#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdexcept> 

#include <GL/glew.h>

#include "Shader.h"

class MeshShader
{
public:
    MeshShader(const char* vertexShaderLocation, const char* fragmentShaderLocation);

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    GLuint GetAmbientIntensityLocation();
    GLuint GetAmbientColourLocation();
    GLuint GetDiffuseIntensityLocation();
    GLuint GetDirectionLocation();
    GLuint GetCameraPositionLocation();
    GLuint GetSpecularIntensityLocation();
    GLuint GetSpecularShininessLocation();

    void UseShader();
    void ClearShader();

    ~MeshShader();

private:
    Shader shader;
    GLuint uniformProjection, uniformModel, uniformView, uniformAmbientIntesity, uniformAmbientColour, uniformDiffuseIntesity, uniformDirection, uniformCameraPosition, uniformSpecularIntensity, uniformSpecularShininess;
};