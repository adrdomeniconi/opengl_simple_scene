#pragma once

#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <iostream>
#include "PointLight.h"

class SpotLight : public PointLight
{
public:
    SpotLight();
    SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat constant, GLfloat linear, GLfloat exponent, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat coneAngle);

    void UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint directionLocation, GLuint coneAngleLocation) const;

    void SetDirection(glm::vec3 dir);
    void SetPosition(glm::vec3 pos);

    ~SpotLight();

private:
    glm::vec3 direction;
    GLfloat coneAngle, coneAngleProcessed;
};
