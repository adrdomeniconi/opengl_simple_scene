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

GLuint VAO, VBO, IBO, shader, uniformModel, uniformProjection; //IBO is the index buffer object

bool direction = true; //Right
float triOffset = 0.0f;
float triMaxOffset = 0.5f;
float triIncrement = 0.005f;

float currentAngle = 0.0f;

float minSize = 0.1f;
float maxSize = 1.0f;
float sizeDirection = true;
float sizeOffset = 0.4f;
float sizeIncrement = 0.01f;

//This example shows passing a variable from the vertex shader to the fragment shader.

static const char* vertexShader = "                                         \n\
# version 330                                                               \n\
                                                                            \n\
layout (location = 0) in vec3 pos;                                          \n\
out vec4 vColour;                                          \n\
uniform mat4 model;                                                         \n\
uniform mat4 projection;                                                         \n\
                                                                            \n\
void main()                                                                 \n\
{                                                                           \n\
    gl_Position = projection * model * vec4(pos, 1.0);                                   \n\
    vColour = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);                           \n\
}                                                                           \n\
";

static const char* fragmentShader = "                                       \n\
# version 330                                                               \n\
                                                                            \n\
in vec4 vColour;                                                            \n\
out vec4 colour;                                                            \n\
                                                                            \n\
void main()                                                                 \n\
{                                                                           \n\
    colour = vec4(vColour);                                                 \n\
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
    }

    // Access a variable of the shader
    uniformModel = glGetUniformLocation(shader, "model");
    uniformProjection = glGetUniformLocation(shader, "projection");
}

void CreateObject()
{
    unsigned int indices[] = {
        0, 1, 4,
        1, 2, 4,
        2, 3, 4,
        3, 0, 4
    };

    GLfloat vertices[] = {
        -1.0f, -1.0f, -1.0f,
        1.0f, -1.0, -1.0f,
        1.0f, -1.0f, 1.0f,
        -1.0f, -1.0f, 1.0f,
        0.0, 1.0f, 0.0f
    };

    //Configure the VAO
    //Get the VAO ID
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //Configure the VBO for the VAO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //Since we're not changing the values on the vertex, it should be static draw.

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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

    glEnable(GL_DEPTH_TEST); // Used to define which pixel should be draw when a face is in front of the other

    //Setup viewport size
    glViewport(0, 0, bufferWidth, bufferHeight);

    CreateObject();
    CompileShaders();

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)bufferWidth/(GLfloat)bufferHeight, 0.1f, 100.0f);

    //Main while
    while(!glfwWindowShouldClose(mainWindow))
    {
        // Get + handle user input events
        glfwPollEvents();

        currentAngle += 0.2f;
        if(currentAngle >= 360)
        {
            currentAngle = 0;
        }

        if(direction) 
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

        // Clear window
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //Run the program using the specified shader
        glUseProgram(shader);

        //Identity matrix 4x4 
        glm::mat4 model(1.0f);
       
        model = glm::translate(model, glm::vec3(0.0f, triOffset, -2.0f));
        model = glm::rotate(model, currentAngle * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
        model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

        //Apply the offset value in the shader uniform xMove;
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
        glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        glUseProgram(0);

        // Swap the hidden screen (the next draw screen) with the current screen
        glfwSwapBuffers(mainWindow);
    }

    return 0;
}