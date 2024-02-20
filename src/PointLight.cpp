#include "PointLight.h"

PointLight::PointLight() : PointLight(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f) { }

PointLight::PointLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat constant, GLfloat linear, GLfloat exponent) : 
    Light(red, green, blue, ambientIntensity, diffuseIntensity), 
    position(glm::vec3(xPos, yPos, zPos)), 
    constant(constant), 
    linear(linear), 
    exponent(exponent)
{
}

void PointLight::UseLight(GLfloat ambientIntesityLocation, GLfloat ambientColourLocation, GLfloat diffuseIntensityLocation, GLfloat positionLocation, GLfloat constantLocation, GLfloat linearLocation, GLfloat exponentLocation)
{
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntesityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
    
    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, linear);
}


PointLight::~PointLight()
{
}
