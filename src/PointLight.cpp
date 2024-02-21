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

void PointLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint positionLocation, GLuint constantLocation, GLuint linearLocation, GLuint exponentLocation) const
{
    std::cout << "PointLight!" << std::endl;
    std::cout << "ambientIntensityLocation: " << ambientIntensityLocation << std::endl;
    std::cout << "ambientColourLocation: " << ambientColourLocation << std::endl;
    std::cout << "diffuseIntensityLocation: " << diffuseIntensityLocation << std::endl;
    std::cout << "positionLocation: " << positionLocation << std::endl;
    std::cout << "constantLocation: " << constantLocation << std::endl;
    std::cout << "linearLocation: " << linearLocation << std::endl;
    std::cout << "exponentLocation: " << exponentLocation << std::endl;

    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
    
    glUniform3f(positionLocation, position.x, position.y, position.z);
    glUniform1f(constantLocation, constant);
    glUniform1f(linearLocation, linear);
    glUniform1f(exponentLocation, linear);
}


PointLight::~PointLight()
{
}
