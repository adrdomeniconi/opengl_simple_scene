#pragma once
#include "Light.h"

class PointLight : 
    public Light
{
public:
    PointLight();
    PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat constant, GLfloat linear, GLfloat exponenet);

    void UseLight(GLfloat ambientIntesityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat positionLocation, GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation);

    ~PointLight();

private:
    glm::vec3 position;
    GLfloat constant, linear, exponent;
};