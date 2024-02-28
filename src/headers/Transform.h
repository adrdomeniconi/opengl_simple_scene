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
    void Apply(GLuint modelLocation);

    ~Transform();

private:
    glm::mat4 _model; 
    glm::vec3 _translate;
    glm::vec3 _rotate;
    glm::vec3 _rotateRadians;
    glm::vec3 _scale;
};