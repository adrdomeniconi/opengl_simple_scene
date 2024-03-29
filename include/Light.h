#pragma once

#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <iostream>

class Light
{
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity);

    void UseLight(GLfloat ambientIntesityLocation, GLfloat ambienColourLocation, GLfloat diffuseIntensityLocation) const;

    ~Light();

protected:
    glm::vec3 colour;
    GLfloat ambientIntensity;
    GLfloat diffuseIntensity;
};