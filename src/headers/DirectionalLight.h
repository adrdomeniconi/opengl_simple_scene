#pragma once
#include "Light.h"

class DirectionalLight : 
    public Light
{
public:
    DirectionalLight();
    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuseIntensity);

    void UseLight(GLfloat ambientIntesityLocation, GLfloat ambienColourLocation, GLfloat diffuseIntensityLocation, GLfloat directionLocation);

    ~DirectionalLight();

private:
    glm::vec3 direction;
};