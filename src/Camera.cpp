#include "Camera.h"
#include <iostream>
#include <algorithm>

Camera::Camera() { }

Camera::Camera(glm::vec3 startPosition, glm::vec3 startUp, GLfloat startYaw, GLfloat startPitch, GLfloat startMoveSpeed, GLfloat startTurnSpeed) : 
    position(startPosition),
    worldUp(startUp),
    yaw(startYaw),
    pitch(startPitch),
    front(glm::vec3(0.0f, 0.0f, -1.0f)),
    movementSpeed(startMoveSpeed),
    turnSpeed(startTurnSpeed)
{
    update();
}

void Camera::keyControl(bool *keys, GLfloat deltaTime)
{
    GLfloat adjustedMovementSpeed = movementSpeed * deltaTime;

    if(keys[GLFW_KEY_W])
    {
        position += front * adjustedMovementSpeed;
    }

    if(keys[GLFW_KEY_S])
    {
        position -= front * adjustedMovementSpeed;
    }

    if(keys[GLFW_KEY_D])
    {
        position += right * adjustedMovementSpeed;
    }

    if(keys[GLFW_KEY_A])
    {
        position -= right * adjustedMovementSpeed;
    }
}

void Camera::mouseControl(GLfloat deltaX, GLfloat deltaY)
{
    deltaX *= turnSpeed;
    deltaY *= turnSpeed;

    yaw += deltaX;
    pitch -= deltaY;

    pitch = std::clamp(pitch, -89.0f, 89.0f);

    update();
}

glm::vec3 Camera::GetPosition()
{
    return position;
}

glm::mat4 Camera::calculateViewMatrix()
{
    return glm::lookAt(position, position + front, up);
}

Camera::~Camera()
{
    
}

void Camera::update()
{
    front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    //This only make sense because this camera has no roll movement. So that the UP will always be the worldUp.
    right = glm::normalize(glm::cross(front, worldUp));
    up = glm::normalize(glm::cross(right, front));
}
