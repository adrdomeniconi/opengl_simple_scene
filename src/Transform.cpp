#include "Transform.h"

Transform::Transform() : 
    _transformationMatrix(glm::mat4(1.0f)),
    _translation(glm::vec3(0.0f, 0.0f, 0.0f)),
    _rotation(glm::vec3(0.0f, 0.0f, 0.0f)),
    _scale(glm::vec3(1.0f, 1.0f, 1.0f)),
    _rotationRadians(glm::vec3(0.0f, 0.0f, 0.0f))
{
    //Do nothing
}

void Transform::Translate(GLfloat x, GLfloat y, GLfloat z)
{
    _translation = glm::vec3(x, y, z);
    // std::cout << _translate.x << ", " << _translate.y << ", " << _translate.z << std::endl;
}

void Transform::Rotate(GLfloat x, GLfloat y, GLfloat z)
{
    _rotation = glm::vec3(x, y, z);
    _rotationRadians = glm::vec3(glm::radians(x), glm::radians(y), glm::radians(z));
}

void Transform::Scale(GLfloat x, GLfloat y, GLfloat z)
{
    _scale = glm::vec3(x, y, z);
}

void Transform::Scale(GLfloat factor)
{
    _scale = glm::vec3(factor, factor, factor);
}

glm::vec3 Transform::Translation()
{
    return _translation;
}

glm::vec3 Transform::Rotation()
{
    return _rotationRadians;
}

glm::vec3 Transform::Scale()
{
    return _scale;
}

glm::mat4 Transform::TransformationMatrix()
{
    glm::mat4 tMatrix = glm::mat4(1.0f);

    tMatrix = glm::translate(tMatrix, _translation);

    if (_rotationRadians.x != 0.0f)
    {
        tMatrix = glm::rotate(tMatrix, _rotationRadians.x, glm::vec3(1.0f, 0.0f, 0.0f));
    }

    if (_rotationRadians.y != 0.0f)
    {
        tMatrix = glm::rotate(tMatrix, _rotationRadians.y, glm::vec3(0.0f, 1.0f, 0.0f));
    }

    if (_rotationRadians.z != 0.0f)
    {
        tMatrix = glm::rotate(tMatrix, _rotationRadians.z, glm::vec3(0.0f, 0.0f, 1.0f));
    }

    tMatrix = glm::scale(tMatrix, _scale);

    return tMatrix;
}

void Transform::Apply(GLuint modelLocation, const glm::mat4 parentMatrix)
{
    _transformationMatrix = parentMatrix * TransformationMatrix();
    glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(_transformationMatrix));
}

void Transform::printMatrix(const glm::mat4 matrix)
{
    for(int i = 0 ; i < 4 ; i++)
    {
        for(int j = 0 ; j < 4 ; j++)
        {
            std::cout << matrix[j][i] << " ";
        }
        std::cout << std::endl;
    }
}

Transform::~Transform()
{
}
