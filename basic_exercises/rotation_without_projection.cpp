#include <stdio.h>
#include <string.h>
#include <cmath>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>


const GLint WINDOW_WIDTH = 800, WINDOW_HEIGHT = 600; 
const float toRadians = 3.14159265 / 180.0f;

GLuint VAO, VBO, shader, uniformModel;

bool direction = true; //Right
float triOffset = 0.0f;
float triMaxOffset = 0.5f;
float triIncrement = 0.005f;
float currentAngle = 0.0f;

//A simple veriable will be runn for every point passed to the shader
//With uniform variables the same variable is applied to the points.  

static const char* vertexShader = "                                         \n\
# version 330                                                               \n\
                                                                            \n\
layout (location = 0) in vec3 pos;                                          \n\
uniform mat4 model;                                                        \n\
                                                                            \n\
void main()                                                                 \n\
{                                                                           \n\
    gl_Position = model * vec4(0.4 * pos.x, 0.4 * pos.y, pos.z, 1.0);       \n\
}                                                                           \n\
";

static const char* fragmentShader = "                                       \n\
# version 330                                                               \n\
                                                                            \n\
out vec4 colour;                                                            \n\
                                                                            \n\
void main()                                                                 \n\
{                                                                           \n\
    colour = vec4(1.0, 0.0, 0.0, 1.0);                                      \n\
}                                                                           \n\
";

void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
    GLuint theShader = glCreateShader(shaderType);

    //Get and compile the shader code
    const GLchar* theCode[1];
    theCode[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(theShader, 1, theCode, codeLength);
    glCompileShader(theShader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 }; 

    glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
    if(!result)
    {
        glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
        printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    //Attach the compiled shader to the program
    glAttachShader(theProgram, theShader);
}

void CompileShaders() {
    shader = glCreateProgram();
    if(!shader) {
        printf("Error creating shader program.\n");
        return;
    }

    AddShader(shader, vertexShader, GL_VERTEX_SHADER);
    AddShader(shader, fragmentShader, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 }; 

    //Create the executable on the graphics card
    glLinkProgram(shader);
    glGetProgramiv(shader, GL_LINK_STATUS, &result);
    if(!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return;
    }

    //Just validate if it worked
    glValidateProgram(shader);
    glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
    if(!result)
    {
        glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
        return;
    }

    // Access a variable of the shader
    uniformModel = glGetUniformLocation(shader, "model");
}

void CreateTriangle()
{
    GLfloat vertices[] = {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0, 1.0f, 0.0f
    };

    //Configure the VAO
    //Get the VAO ID
    glGenVertexArrays(1, &VAO);
    
    glBindVertexArray(VAO);

    //Configure the VBO for the VAO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Since we're not changing the values on the vertex, it should be static draw.

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
    //End configuring the VAO
}

int main() 
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

    GLFWwindow *mainWindow = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Test Window", NULL, NULL);

    if(!mainWindow)
    {
        printf("GLFW window creation failed!");
        glfwTerminate();
        return 1;
    }

    //Get Buffer sixe information
    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

    //Set context for GLEW to use (the current monitor)
    glfwMakeContextCurrent(mainWindow);

    //Allow modern extension features
    glewExperimental = GL_TRUE;

    if(glewInit() != GLEW_OK)
    {
        printf("Glew initialization failed");
        glfwDestroyWindow(mainWindow);
        glfwTerminate();
        return 1;
    }

    //Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    CreateTriangle();
    CompileShaders();

    //Main while
    while(!glfwWindowShouldClose(mainWindow))
    {
        // Get + handle user input events
        glfwPollEvents();

        if(direction) //If it's going to the right
        {
            triOffset += triIncrement;
        }
        else
        {
            triOffset -= triIncrement;
        }

        if(abs(triOffset) >= triMaxOffset)
        {
            direction = !direction;
        }

        currentAngle += 0.1f;
        if(currentAngle >= 360)
        {
            currentAngle = 0;
        }

        // Clear window
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //Run the program using the specified shader
        glUseProgram(shader);

        //Identity matrix 4x4 
        glm::mat4 model(1.0f);

        //Apply a translation to the identity matrix
        model = glm::translate(model, glm::vec3(triOffset, 0.0f, 0.0f));
        model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));

        //Apply the offset value in the shader uniform xMove;
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glBindVertexArray(0);

        glUseProgram(0);

        // Swap the hidden screen (the next draw screen) with the current screen
        glfwSwapBuffers(mainWindow);
    }

    return 0;
}