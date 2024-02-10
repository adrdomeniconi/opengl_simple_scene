#pragma once

#include <stdio.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class MainWindow
{
public:
    MainWindow();
    MainWindow(GLint width, GLint height);

    int Initialize();

    GLfloat getBufferWidth() { return bufferWidth; }
    GLfloat getBufferHeight() { return bufferHeight; }

    bool getShouldClose() { return glfwWindowShouldClose(mainWindow); }
    void swapBuffers() { glfwSwapBuffers(mainWindow); }

    bool* getKeys() { return keys; }
    GLfloat getDeltaX();
    GLfloat getDeltaY();

    ~MainWindow();

private:
    GLFWwindow *mainWindow;
    GLint width, height;
    GLint bufferWidth, bufferHeight;

    GLfloat lastX, lastY;
    GLfloat deltaX, deltaY;
    bool mouseFirstMoved;

    bool keys[1024];

    void createCallbacks();
    static void handleKeys(GLFWwindow* window, int key, int code, int action, int mode);
    static void handleMouse(GLFWwindow* windows, double xPos, double yPos);
};