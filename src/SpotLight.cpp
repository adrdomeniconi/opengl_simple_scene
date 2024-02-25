#include "SpotLight.h"

SpotLight::SpotLight() : SpotLight(1.0f, 1.0f, 1.0f, 0.0, 0.5, 0.0f, 0.0f, 0.0f, .3f, .2f, .1f, 0.0f, -1.0f, 0.0f, 45) { }

SpotLight::SpotLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat ambientIntensity, GLfloat diffuseIntensity, GLfloat xPos, GLfloat yPos, GLfloat zPos, GLfloat exponent, GLfloat linear, GLfloat constant, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat coneAngle) : 
    PointLight(red, green, blue, ambientIntensity, diffuseIntensity, xPos, yPos, zPos, exponent, linear, constant), 
    coneAngle(coneAngle), 
    direction(glm::vec3(xDir, yDir, zDir)), 
    coneAngleProcessed(cosf(glm::radians(coneAngle)))
{
}

void SpotLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation, GLuint directionLocation, GLuint coneAngleLocation) const
{
    // std::cout << "SpotLight!" << std::endl;
    // std::cout << "ambientIntensityLocation: " << ambientIntensityLocation << std::endl;
    // std::cout << "ambientColourLocation: " << ambientColourLocation << std::endl;
    // std::cout << "diffuseIntensityLocation: " << diffuseIntensityLocation << std::endl;
    // std::cout << "positionLocation: " << positionLocation << std::endl;
    // std::cout << "constantLocation: " << constantLocation << std::endl;
    // std::cout << "linearLocation: " << linearLocation << std::endl;
    // std::cout << "exponentLocation: " << exponentLocation << std::endl;
    // std::cout << "directionLocation: " << directionLocation << std::endl;
    // std::cout << "coneAngleLocation: " << coneAngleLocation << std::endl;

    // std::cout << "colour: " << colour.x << ", " << colour.y << ", " << colour.z << ", " << std::endl;
    // std::cout << "ambientIntensity: " << ambientIntensity << std::endl;
    // std::cout << "diffuseIntensity: " << diffuseIntensity << std::endl;
    // std::cout << "position: " << position.x << ", " << position.y << ", " << position.z << ", " << std::endl;
    // std::cout << "constant: " << constant << std::endl;
    // std::cout << "linear: " << linear << std::endl;
    // std::cout << "exponent: " << exponent << std::endl;
    // std::cout << "direction: " << direction.x << ", " << direction.y << ", " << direction.z << ", " << std::endl;
    // std::cout << "coneAngleProcessed: " << coneAngleProcessed << std::endl;

    PointLight::UseLight(ambientIntensityLocation, ambientColourLocation, diffuseIntensityLocation, positionLocation, constantLocation, linearLocation, exponentLocation);
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(coneAngleLocation, coneAngleProcessed);
}

void SpotLight::SetDirection(glm::vec3 dir)
{
    direction = dir;
}
void SpotLight::SetPosition(glm::vec3 pos)
{
    position = pos;
}

SpotLight::~SpotLight()
{
}
