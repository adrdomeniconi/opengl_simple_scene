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
#include "Camera.h"
#include "NormalsVisualizer.h"
#include "Scenes/SampleScene.h"
#include "ShaderLibrary.h"
#include "TextureLibrary.h"
#include "MaterialLibrary.h"

#include <assimp\Importer.hpp>

MainWindow mainWindow;
Camera camera;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

void ClearWindow()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

int main() 
{
    mainWindow = MainWindow(800, 600);
    mainWindow.Initialize();

    camera = Camera(glm::vec3(0.0f, 0.5f, 2.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.1f);

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth()/(GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    TextureLibrary* textureLibrary = new TextureLibrary();
    MaterialLibrary* materialLibrary = new MaterialLibrary();
    ShaderLibrary* shaderLibrary = new ShaderLibrary();

    SampleScene* scene = new SampleScene(textureLibrary, materialLibrary, shaderLibrary);

    ShaderLine* lineShader = dynamic_cast<ShaderLine*>(shaderLibrary->GetShader(ShaderLibrary::ShaderType::Line));
    NormalsVisualizer pyramidANormalsVisualizer = NormalsVisualizer(scene->GetStageMeshObjects(0));
    NormalsVisualizer pyramidBNormalsVisualizer = NormalsVisualizer(scene->GetStageMeshObjects(1));
    NormalsVisualizer floorNormalsVisualizer = NormalsVisualizer(scene->GetStageMeshObjects(2));

    // Model* stageModelObject = scene->GetStageModelObjects(0);
    // std::vector<NormalsVisualizer> modelNormalsVisualizer;

    // for(MeshObject* mesh : stageModelObject->GetMeshObjects())
    // {
    //     modelNormalsVisualizer.push_back(NormalsVisualizer(mesh));
    // }

    while(!mainWindow.getShouldClose())
    {
        GLfloat now = glfwGetTime();
        deltaTime = now - lastTime;
        lastTime = now;

        glfwPollEvents();

        camera.keyControl(mainWindow.getKeys(), deltaTime);
        camera.mouseControl(mainWindow.getDeltaX(), mainWindow.getDeltaY());

        ClearWindow();

        scene->Update(camera, projection);

        lineShader->UseShader();
        glUniformMatrix4fv(lineShader->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
        glUniformMatrix4fv(lineShader->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));

        pyramidANormalsVisualizer.Render(lineShader);
        pyramidBNormalsVisualizer.Render(lineShader);
        floorNormalsVisualizer.Render(lineShader);

        // for(NormalsVisualizer nv : modelNormalsVisualizer)
        // {
        //     nv.Render(lineShader);
        // }

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}
