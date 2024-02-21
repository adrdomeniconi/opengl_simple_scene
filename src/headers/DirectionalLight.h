#pragma once
#include "Light.h"

class DirectionalLight : 
    public Light
{
public:
    DirectionalLight();
    DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuseIntensity);

    void UseLight(GLuint ambientIntesityLocation, GLuint ambienColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation);

    ~DirectionalLight();

private:
    glm::vec3 direction;
};