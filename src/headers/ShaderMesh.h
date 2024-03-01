#pragma once

#include <stdio.h>
#include <string>
#include <iostream>
#include <stdexcept> 

#include <GL/glew.h>

#include "Shader.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"

class ShaderMesh : public Shader
{
public:
    static const unsigned int MAX_POINT_LIGHTS_COUNT = 3;
    static const unsigned int MAX_SPOT_LIGHTS_COUNT = 3;

    ShaderMesh(const char* vertexShaderLocation, const char* fragmentShaderLocation);

    GLuint GetProjectionLocation();
    GLuint GetModelLocation();
    GLuint GetViewLocation();
    GLuint GetCameraPositionLocation();
    GLuint GetSpecularIntensityLocation();
    GLuint GetSpecularShininessLocation();

    void SetDirectionalLight(DirectionalLight directionalLight);
    void SetPointLights(const std::vector<PointLight> pointLights);
    void SetSpotLights(const std::vector<SpotLight> spotLights);

~ShaderMesh();

private:
    unsigned int pointLightsCount;
    unsigned int spotLightsCount;

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

    } uniformPointLights[MAX_POINT_LIGHTS_COUNT];

    GLfloat uniformPointLightsCount;

    struct {
        GLfloat ambientIntesity;
        GLfloat ambientColour;
        GLfloat diffuseIntesity;

        GLfloat position; 
        GLfloat constant; 
        GLfloat linear; 
        GLfloat exponent;

        GLfloat direction;
        GLfloat coneAngle;
    } uniformSpotLights[MAX_SPOT_LIGHTS_COUNT];

    GLfloat uniformSpotLightsCount;

    GLuint shaderID;
    GLuint uniformProjection, uniformModel, uniformView, uniformCameraPosition, uniformSpecularIntensity, uniformSpecularShininess;

    void getPointLightUniformLocations();
    void getSpotLightUniformLocations();
    void getDirectionalLightUniformLocations();
};