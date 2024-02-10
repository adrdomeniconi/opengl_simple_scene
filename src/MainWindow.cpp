#include <MainWindow.h>
#include <iostream>

MainWindow::MainWindow() : MainWindow(800, 600) {}

MainWindow::MainWindow(GLint width, GLint height) : width(width), height(height) 
{
    deltaX = 0.0f;
    deltaY = 0.0f;
    mouseFirstMoved = true;

    for(size_t i = 0; i < 1024; i++)
    {
        keys[i] = 0;
    }
}

int MainWindow::Initialize()
{
    if(!glfwInit())
    {
        printf("GLFW initialisation failed!");
        glfwTerminate();
        return 1;
    }

    //Set the Open GL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Setting the core profile to not allow backwards compatibility
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Allow forward compatibility
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
    std::cout << "width: " << width << " height: " << height << std::endl;

    mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
    if(!mainWindow)
    {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return 1;
    }

    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //Set context for GLEW to use (the current monitor)
    glfwMakeContextCurrent(mainWindow);

    createCallbacks();
    glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    //Allow modern extension features
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        printf("Glew initialization failed");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    glEnable(GL_DEPTH_TEST); // Used to define which pixel should be draw when a face is in front of the other

    //Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    //Set the current window on the GLFW
    glfwSetWindowUserPointer(mainWindow, this);

    return 0;
}

void MainWindow::createCallbacks()
{
    glfwSetKeyCallback(mainWindow, handleKeys);
    glfwSetCursorPosCallback(mainWindow, handleMouse);
}

GLfloat MainWindow::getDeltaX() 
{ 
    GLfloat delta = deltaX;
    deltaX = 0;
    return delta; 
}

GLfloat MainWindow::getDeltaY() 
{ 
    GLfloat delta = deltaY;
    deltaY = 0;
    return delta; 
}

void MainWindow::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    // Baiscally it's retrieving back the mainWindow that was set when calling glfwSetWindowUserPointer on the Initialize function.
    MainWindow* currentWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));

    if(key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }

    //Just validating if it's a valid key
    if(key < 0 || key > 1024) {return;}

    if(action == GLFW_PRESS)
    {
        currentWindow->keys[key] = true;
        // std::cout << "Pressed: " << key << std::endl;
    }
    else if (action == GLFW_RELEASE)
    {
        currentWindow->keys[key] = false;
        // std::cout << "Released: " << key << std::endl;
    }
}

void MainWindow::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
    // Baiscally it's retrieving back the mainWindow that was set when calling glfwSetWindowUserPointer on the Initialize function.
    MainWindow* currentWindow = static_cast<MainWindow*>(glfwGetWindowUserPointer(window));

    if(currentWindow->mouseFirstMoved)
    {
        currentWindow->lastX = xPos;
        currentWindow->lastY = yPos;
        currentWindow->mouseFirstMoved = false;
    }

    currentWindow->deltaX = xPos - currentWindow->lastX;
    currentWindow->deltaY = yPos - currentWindow->lastY;

    currentWindow->lastX = xPos;
    currentWindow->lastY = yPos;
}

MainWindow::~MainWindow()
{
    glfwDestroyWindow(mainWindow);
    glfwTerminate();
}