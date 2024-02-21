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
    static const unsigned int MAX_POINT_LIGHTS_COUNT = 3;

    MeshShader(const char* vertexShaderLocation, const char* fragmentShaderLocation);

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    GLuint GetCameraPositionLocation();
    GLuint GetSpecularIntensityLocation();
    GLuint GetSpecularShininessLocation();

    void SetDirectionalLight(DirectionalLight *directionalLight);
    void SetPointLights(const std::vector<PointLight*>& pointLights);

    void UseShader();
    void ClearShader();

~MeshShader();

private:
    Shader shader;
    unsigned int pointLightsCount;

    struct {
        GLfloat ambientIntesity;
        GLfloat ambientColour;
        GLfloat diffuseIntesity;
        GLfloat direction;

    } uniformDirectionalLight;

    struct {
        GLfloat ambientIntesity;
        GLfloat ambientColour;
        GLfloat diffuseIntesity;
        GLfloat position; 
        GLfloat constant; 
        GLfloat linear; 
        GLfloat exponent;

    } uniformPointLight[MAX_POINT_LIGHTS_COUNT];

    GLuint uniformProjection, uniformModel, uniformView, uniformCameraPosition, uniformSpecularIntensity, uniformSpecularShininess, uniformPointLightsCount;

    void getPointLightUniformLocations(GLuint shaderID);
    void getDirectionalLightUniformLocations(GLuint shaderID);
};