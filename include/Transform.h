#pragma once

#include <GLM/glm.hpp>
#include <GL/glew.h>
#include <GLM/gtc/type_ptr.hpp>
#include <iostream>

class Transform
{
public:

    Transform();

    void Translate(GLfloat x, GLfloat y, GLfloat z);
    void Rotate(GLfloat x, GLfloat y, GLfloat z);
    void Scale(GLfloat x, GLfloat y, GLfloat z);
    void Scale(GLfloat factor);

    glm::vec3 Translation();
    glm::vec3 Rotation();
    glm::vec3 Scale();
    glm::mat4 Model();

    void Apply(GLuint modelLocation);
    void updateModel();
    void Apply(GLuint modelLocation, const glm::mat4 parentMatrix);

    ~Transform();

private:
    glm::mat4 _model; 
    glm::vec3 _translation;
    glm::vec3 _rotation;
    glm::vec3 _rotationRadians;
    glm::vec3 _scale;
};