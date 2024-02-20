#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdexcept> 

#include <GL/glew.h>

#include "Shader.h"
#include "DirectionalLight.h"
#include "PointLight.h"

class MeshShader
{
public:
    static const unsigned int MAX_POINT_LIGHT_COUNT = 3;

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

    void SetDirectionalLight(DirectionalLight *directionalLight);
    // void AddPointLight(PointLight *pointLight);

    void UseShader();
    void ClearShader();

    ~MeshShader();

private:
    Shader shader;
    DirectionalLight *directionalLight;
    PointLight pointLights[MAX_POINT_LIGHT_COUNT];
    unsigned int pointLightsCount;
    GLuint uniformProjection, uniformModel, uniformView, uniformAmbientIntesity, uniformAmbientColour, uniformDiffuseIntesity, uniformDirection, uniformCameraPosition, uniformSpecularIntensity, uniformSpecularShininess;
};