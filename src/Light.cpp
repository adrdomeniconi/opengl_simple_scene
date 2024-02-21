#include "Light.h"
#include <iostream>

Light::Light(): Light(1.0f, 1.0f, 1.0f, 1.0f, 1.0) {}

Light::Light(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat diffuseIntensity) : 
    colour(glm::vec3(red, green, blue)), 
    ambientIntensity(intensity),
    diffuseIntensity(diffuseIntensity)  { }

void Light::UseLight(GLfloat ambientIntesityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation) const
{
    // Just passes these values to locations on the shader
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntesityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

Light::~Light()
{
}
