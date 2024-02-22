#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(): DirectionalLight(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0) {}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuseIntensity)
        : Light(red, green, blue, intensity, diffuseIntensity), 
          direction(glm::vec3(xDir, yDir, zDir)) 
{
        
}

void DirectionalLight::UseLight(GLuint ambientIntensityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation)
{   
    // std::cout << "PointLight!" << std::endl;
    // std::cout << "ambientIntensityLocation: " << ambientIntensityLocation << std::endl;
    // std::cout << "ambientColourLocation: " << ambientColourLocation << std::endl;
    // std::cout << "diffuseIntensityLocation: " << diffuseIntensityLocation << std::endl;
    // std::cout << "directionLocation: " << directionLocation << std::endl;
    // Just passes these values to locations on the shader
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntensityLocation, ambientIntensity);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
    
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
}

DirectionalLight::~DirectionalLight()
{
}
