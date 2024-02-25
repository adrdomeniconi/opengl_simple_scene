#include "SpotLight.h"

SpotLight::SpotLight() : SpotLight(1.0f, 1.0f, 1.0f, 0.0, 0.5, 0.0f, 0.0f, 0.0f, .3f, .2f, .1f, 0.0f, -1.0f, 0.0f, 45) { }

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat constant, GLfloat linear, GLfloat exponent, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat coneAngle) : 
    PointLight(red, green, blue, ambientIntensity, diffuseIntensity, xPos, yPos, zPos, constant, linear, exponent), 
    coneAngle(coneAngle), 
    direction(glm::vec3(yDir, xDir, zDir)), 
    coneAngleProcessed(cosf(glm::radians(coneAngle)))
{
}

void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint directionLocation, GLuint coneAngleLocation) const
{
    PointLight::UseLight(ambientIntensityLocation, ambientColourLocation, diffuseIntensityLocation, positionLocation, constantLocation, linearLocation, exponentLocation);
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(coneAngleLocation, coneAngleProcessed);
}

void SpotLight::SetDirection(glm::vec3 dir)
{
    direction = dir;
}

SpotLight::~SpotLight()
{
}
