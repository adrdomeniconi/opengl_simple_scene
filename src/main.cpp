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
// #include "DirectionalLight.h"
// #include "PointLight.h"
// #include "SpotLight.h"
#include "Line.h"
#include "MeshObject.h"
#include "NormalsVisualizer.h"
#include "AverageNormalsCalculator.h"
#include "Scenes/SampleScene.h"

MainWindow mainWindow;
Camera camera;

// DirectionalLight mainLight;
// std::vector<PointLight> pointLights;
// std::vector<SpotLight> spotLights;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

int main() 
{
    mainWindow = MainWindow(800, 600);
    mainWindow.Initialize();

    camera = Camera(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.1f);

    // mainLight = DirectionalLight(0.0f, 1.0f, 0.0f, 0.2f, 0.5f, -1.0f, 1.5f, 0.4f);
    // pointLights.push_back(PointLight(1.0f, 0.0f, 0.0f, 0.2f, 0.7f, 2.0f, 1.5f, 2.0f, 0.1f, 0.2f, 0.3f));
    // spotLights.push_back(SpotLight(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.2f, 0.0f, 0.0f, -1.0f, 0.0f, 20));

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth()/(GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    SampleScene* scene = new SampleScene();

    ShaderMesh* meshShader = dynamic_cast<ShaderMesh*>(scene->shaderLibrary.GetShader(ShaderLibrary::ShaderType::Mesh));
    ShaderLine* lineShader = dynamic_cast<ShaderLine*>(scene->shaderLibrary.GetShader(ShaderLibrary::ShaderType::Line));

    NormalsVisualizer pyramidANormalsVisualizer = NormalsVisualizer(scene->GetStageObjects(0));
    NormalsVisualizer pyramidBNormalsVisualizer = NormalsVisualizer(scene->GetStageObjects(1));
    NormalsVisualizer floorNormalsVisualizer = NormalsVisualizer(scene->GetStageObjects(2));

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

        // spotLights[0].SetDirection(camera.GetDirection());
        // spotLights[0].SetPosition(camera.GetPosition());
        scene->Update(camera, projection);

        //Configure the Line shader
        lineShader->UseShader();
        glUniformMatrix4fv(lineShader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(lineShader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
      
        for(auto meshObject : scene->GetStageObjects())
        {
            meshObject.Render();
        }

        pyramidANormalsVisualizer.Render(lineShader);
        pyramidBNormalsVisualizer.Render(lineShader);
        floorNormalsVisualizer.Render(lineShader);

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}