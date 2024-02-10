#pragma once

#include <GLM/glm.hpp>
#include <GL/glew.h>

class Light
{
public:
    Light();
    Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuseIntensity);

    void UseLight(GLuint ambientIntesityLocation, GLuint ambienColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation);

    ~Light();

private:
    glm::vec3 colour;
    GLfloat ambientIntensity;

    glm::vec3 direction;
    GLfloat diffuseIntensity;
};