#pragma once

#include <GL/glew.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>

#include <GLFW/glfw3.h>

class Camera
{
public:
    Camera();
    Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed);

    void keyControl(bool* keys, GLfloat deltaTime);
    void mouseControl(GLfloat deltaX, GLfloat deltaY);

    glm::vec3 GetPosition();
    glm::vec3 GetDirection();

    glm::mat4 calculateViewMatrix();

    ~Camera();

private:
    glm::vec3 position; 
    glm::vec3 front;
    glm::vec3 up; 
    glm::vec3 right; 
    glm::vec3 worldUp;

    GLfloat yaw;
    GLfloat pitch;

    GLfloat movementSpeed; 
    GLfloat turnSpeed;

    void update();

};