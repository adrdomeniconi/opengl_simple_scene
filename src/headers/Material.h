#pragma once

#include <GL/glew.h>

class Material
{
public:
    Material();
    Material(GLfloat specularIntensity, GLfloat shininess);
    ~Material();

    void Use(GLuint specularIntensityLocation, GLuint shininessLocation);

private:
    GLfloat specularIntensity;
    GLfloat shininess;
};