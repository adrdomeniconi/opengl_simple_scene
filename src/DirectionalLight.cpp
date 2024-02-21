#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(): DirectionalLight(1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 1.0) {}

DirectionalLight::DirectionalLight(GLfloat red, GLfloat green, GLfloat blue, GLfloat intensity, GLfloat xDir, GLfloat yDir, GLfloat zDir, GLfloat diffuseIntensity)
        : Light(red, green, blue, intensity, diffuseIntensity), 
          direction(glm::vec3(xDir, yDir, zDir)) 
{
        
}

void DirectionalLight::UseLight(GLuint ambientIntesityLocation, GLuint ambientColourLocation, GLuint diffuseIntensityLocation, GLuint directionLocation)
{
    // Just passes these values to locations on the shader
    glUniform3f(ambientColourLocation, colour.x, colour.y, colour.z);
    glUniform1f(ambientIntesityLocation, ambientIntensity);
    
    glUniform3f(directionLocation, direction.x, direction.y, direction.z);
    glUniform1f(diffuseIntensityLocation, diffuseIntensity);
}

DirectionalLight::~DirectionalLight()
{
}
