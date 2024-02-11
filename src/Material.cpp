#include "Material.h"

Material::Material() : Material(0.0f, 0.0f) { }

Material::Material(GLfloat specularIntensity, GLfloat shininess) :
    specularIntensity(specularIntensity),
    shininess(shininess)
{

}

Material::~Material()
{
}

void Material::Use(GLuint specularIntensityLocation, GLuint shininessLocation)
{
    glUniform1f(specularIntensityLocation, specularIntensity);
    glUniform1f(shininessLocation, shininess);
}
