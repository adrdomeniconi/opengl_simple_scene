#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <GLM/glm.hpp>
#include <GLM/gtc/matrix_transform.hpp>
#include <GLM/gtc/type_ptr.hpp>

#include "MainWindow.h"
#include "Mesh.h"
#include "Camera.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Line.h"
#include "MeshObject.h"
#include "NormalsVisualizer.h"
#include "AverageNormalsCalculator.h"
#include "Scenes/SampleScene.h"

const float toRadians = 3.14159265 / 180.0f;

MainWindow mainWindow;
std::vector<Mesh*> meshList;
Camera camera;

DirectionalLight mainLight;
std::vector<std::shared_ptr<PointLight>> pointLights;
std::vector<std::shared_ptr<SpotLight>> spotLights;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

static const char* vertexShader = "Shaders/shader.vert";
static const char* fragmentShader = "Shaders/shader.frag";
static const char* vertexShaderLine = "Shaders/line_shader.vert";
static const char* fragmentShaderLine = "Shaders/line_shader.frag";

void CreatePyramid()
{
    unsigned int indices[] = {
        4, 1, 0,
        4, 2, 1,
        4, 3, 2,
        4, 0, 3
    };

    GLfloat vertices[] = {
    //    x      y      z     u     v     nx    ny    nz
        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.0f,  1.0f,  0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
    };

    const unsigned int indicesCount = sizeof(indices)/sizeof(indices[0]);
    const unsigned int verticesDataCount = sizeof(vertices)/sizeof(vertices[0]);
    const unsigned int VERTEX_LENGTH = 8;
    const unsigned int NORMALS_OFFSET = 5;
    const unsigned int verticesCount = verticesDataCount/VERTEX_LENGTH;

    AverageNormalsCalculator::Calculate(indices, indicesCount, vertices, verticesDataCount, VERTEX_LENGTH, NORMALS_OFFSET);

    Mesh *mesh = new Mesh();
    mesh->CreateMesh(vertices, indices, verticesDataCount, indicesCount, VERTEX_LENGTH, NORMALS_OFFSET);

    meshList.push_back(mesh);
}

void CreateFloor()
{
    unsigned int indices[] = {
        0, 1, 3,
        3, 1, 2 
    };

    GLfloat vertices[] = {
    //    x      y      z     u     v     nx    ny    nz
        -10.0f, 0.0f, -10.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
        -10.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
        10.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
        10.0f, 0.0f, -10.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
    };

    const unsigned int indicesCount = sizeof(indices)/sizeof(GLfloat);
    const unsigned int verticesDataCount = sizeof(vertices)/sizeof(unsigned int);

    Mesh *mesh = new Mesh();
    mesh -> CreateMesh(vertices, indices, verticesDataCount, indicesCount, 8, 5);
    meshList.push_back(mesh);
}

int main() 
{
    mainWindow = MainWindow(800, 600);
    mainWindow.Initialize();

    CreatePyramid();
    CreatePyramid();
    CreateFloor();

    camera = Camera(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.1f);

    mainLight = DirectionalLight(0.0f, 1.0f, 0.0f, 0.2f, 0.5f, -1.0f, 1.5f, 0.4f);

    auto pointLight1 = std::make_shared<PointLight>(1.0f, 0.0f, 0.0f, 0.2f, 0.7f, 2.0f, 1.5f, 2.0f, 0.1f, 0.2f, 0.3f);
    pointLights.push_back(pointLight1);

    auto cameraSpotLight = std::make_shared<SpotLight>(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.2f, 0.0f, 0.0f, -1.0f, 0.0f, 20);
    spotLights.push_back(cameraSpotLight);

    GLuint uniformProjection = 0, 
           uniformModel = 0, 
           uniformView = 0, 
           uniformCameraPosition = 0;

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth()/(GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    SampleScene* scene = new SampleScene();

    ShaderMesh* meshShader = dynamic_cast<ShaderMesh*>(scene->shaderLibrary.GetShader(ShaderLibrary::ShaderType::Mesh));
    ShaderLine* lineShader = dynamic_cast<ShaderLine*>(scene->shaderLibrary.GetShader(ShaderLibrary::ShaderType::Line));

    MeshObject pyramidA = MeshObject(meshList[0], meshShader, scene->materialLibrary.GetMaterial(MaterialLibrary::MaterialType::Shiny), scene->textureLibrary.GetTexture(TextureLibrary::TextureType::Brick));
    MeshObject pyramidB = MeshObject(meshList[1], meshShader, scene->materialLibrary.GetMaterial(MaterialLibrary::MaterialType::Dull), scene->textureLibrary.GetTexture(TextureLibrary::TextureType::Dirt));
    MeshObject floorMesh = MeshObject(meshList[2], meshShader, scene->materialLibrary.GetMaterial(MaterialLibrary::MaterialType::Shiny), scene->textureLibrary.GetTexture(TextureLibrary::TextureType::Floor));

    NormalsVisualizer pyramidANormalsVisualizer = NormalsVisualizer(&pyramidA);
    NormalsVisualizer pyramidBNormalsVisualizer = NormalsVisualizer(&pyramidB);
    NormalsVisualizer floorNormalsVisualizer = NormalsVisualizer(&floorMesh);

    while(!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        // Get + handle user input events
        glfwPollEvents();

        camera.keyControl(mainWindow.getKeys(), deltaTime);
        camera.mouseControl(mainWindow.getDeltaX(), mainWindow.getDeltaY());

        // Clear window
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cameraSpotLight->SetDirection(camera.GetDirection());
        cameraSpotLight->SetPosition(camera.GetPosition());

        //Configure the Mesh shader
        meshShader->UseShader();
        meshShader->SetDirectionalLight(&mainLight);
        meshShader->SetPointLights(pointLights);
        meshShader->SetSpotLights(spotLights);

        glUniformMatrix4fv(meshShader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(meshShader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        glUniform3f(meshShader->GetCameraPositionLocation(), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        //Configure the Line shader
        lineShader->UseShader();
        glUniformMatrix4fv(lineShader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(lineShader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
      
        //First pyramid
        pyramidA.Scale(0.4f, 0.4f, 0.4f);
        pyramidA.Render();
        pyramidANormalsVisualizer.Render(lineShader);

        // Second Pyramid
        pyramidB.Translate(0.0f, .3, -1.5f);
        pyramidB.Scale(0.2f, 0.2f, 0.2f);
        pyramidB.Render();
        pyramidBNormalsVisualizer.Render(lineShader);

        // Floor
        floorMesh.Translate(0.0f, -2.0f, 0.0f);
        floorMesh.Render();
        floorNormalsVisualizer.Render(lineShader);

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}