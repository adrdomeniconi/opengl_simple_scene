#pragma once

#include <GLM/glm.hpp>
#include <GL/glew.h>

class Light
{
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity);

    void UseLight(GLfloat ambientIntesityLocation, GLfloat ambienColourLocation, GLfloat diffuseIntensityLocation);

    ~Light();

protected:
    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};