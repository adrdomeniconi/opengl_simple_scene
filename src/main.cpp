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
#include "MeshShader.h"
#include "Camera.h"
#include "Texture.h"
#include "Light.h"
#include "Material.h"
#include "Line.h"

const float toRadians = 3.14159265 / 180.0f;

MainWindow mainWindow;
std::vector<Mesh*> meshList;
MeshShader *meshShader;
Camera camera;

Texture brickTexture;
Texture dirtTexture;

Light mainLight;

Material shinyMaterial;
Material dullMaterial;

GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;

static const char* vertexShader = "Shaders/shader.vert";
static const char* fragmentShader = "Shaders/shader.frag";

void updateVerticeNormal(GLfloat *vertices, unsigned int verticeIdx, glm::vec3 normal, unsigned int normalOffset)
{
    unsigned int verticeNormalsIdx = verticeIdx + normalOffset;
    vertices[verticeNormalsIdx] += normal.x;
    vertices[verticeNormalsIdx + 1] += normal.y;
    vertices[verticeNormalsIdx + 2] += normal.z;
}

void normalizeVerticesNormals(GLfloat *vertices, unsigned int verticesCount, unsigned int verticesLength, unsigned int normalOffset)
{
    for(size_t i = 0; i < verticesCount/verticesLength; i++)
    {
        unsigned int verticeNormalsIdx = i * verticesLength + normalOffset;
        glm::vec3 normal(vertices[verticeNormalsIdx], vertices[verticeNormalsIdx + 1], vertices[verticeNormalsIdx + 2]);
        normal = glm::normalize(normal);
        updateVerticeNormal(vertices, i * verticesLength, normal, normalOffset);
    }
}

void calculateAverageNormals(unsigned int *indices, unsigned int indicesCount, GLfloat *vertices, unsigned int verticesCount, unsigned int verticesLength, unsigned int normalOffset)
{
    //For each verex the normals are calculated as the average of the triangles of the surfaces that the vertex is part.
    for(size_t i = 0; i < indicesCount; i += 3)
    {
        //Access the position on the vertices array by taking the vertice index on the indices array, and multiplying it by the lenght of entries for each vertice.
        unsigned int vertice0Idx = indices[i] * verticesLength;
        unsigned int vertice1Idx = indices[i+1] * verticesLength;
        unsigned int vertice2Idx = indices[i+2] * verticesLength;

        glm::vec3 vertice0_pos(vertices[vertice0Idx], vertices[vertice0Idx + 1], vertices[vertice0Idx + 2]);
        glm::vec3 vertice1Pos(vertices[vertice1Idx], vertices[vertice1Idx + 1], vertices[vertice1Idx + 2]);
        glm::vec3 vertice2Pos(vertices[vertice2Idx], vertices[vertice2Idx + 1], vertices[vertice2Idx + 2]);

        glm::vec3 edge1 = vertice1Pos - vertice0_pos;
        glm::vec3 edge2 = vertice2Pos - vertice0_pos;

        glm::vec3 normal = glm::cross(edge1, edge2);
        normal = glm::normalize(normal);

        updateVerticeNormal(vertices, vertice0Idx, normal, normalOffset);
        updateVerticeNormal(vertices, vertice1Idx, normal, normalOffset);
        updateVerticeNormal(vertices, vertice2Idx, normal, normalOffset);
    }

    normalizeVerticesNormals(vertices, verticesCount, verticesLength, normalOffset);
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
    //    x      y      z     u     z     nx    ny    nz
        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.0f,  1.0f,  0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
    };

    int indicesCount = sizeof(indices)/sizeof(indices[0]);
    int verticesCount = sizeof(vertices)/sizeof(vertices[0]);

    calculateAverageNormals(indices, indicesCount, vertices, verticesCount, 8, 5);

    Mesh *mesh = new Mesh();
    mesh -> CreateMesh(vertices, indices, verticesCount, indicesCount);
    meshList.push_back(mesh);
}

int main() 
{
    mainWindow = MainWindow(800, 600);
    mainWindow.Initialize();

    CreateObject();
    CreateObject();
    meshShader = new MeshShader(vertexShader, fragmentShader);
    camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.0f, 0.1f);

    brickTexture = Texture("../textures/brick.png");
    brickTexture.LoadTexture();

    dirtTexture = Texture("../textures/dirt.png");
    dirtTexture.LoadTexture();

    mainLight = Light(1.0f, 1.0f, 1.0f, 0.2f, 1.0f, -.5f, -2.0f, 1.0f);

    shinyMaterial = Material(1.0f, 64);
    dullMaterial = Material(1.0f, 32);

    GLuint uniformProjection = 0, 
           uniformModel = 0, 
           uniformView = 0, 
           uniformAmbientIntensity = 0, 
           uniformAmbientColour = 0, 
           uniformDiffuseIntensity = 0, 
           uniformDirection = 0,
           uniformCameraPosition = 0,
           uniformSpecularIntensity = 0,
           uniformSpecularShininess = 0;

    glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth()/(GLfloat)mainWindow.getBufferHeight(), 0.1f, 100.0f);

    //Main while
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

        // meshShader->UseShader();

        // uniformModel = meshShader->GetModelLocation();
        // uniformProjection = meshShader->GetProjectionLocation();
        // uniformView = meshShader->GetViewLocation();
        // uniformAmbientColour = meshShader->GetAmbientColourLocation();
        // uniformAmbientIntensity = meshShader->GetAmbientIntensityLocation();
        // uniformDiffuseIntensity = meshShader->GetDiffuseIntensityLocation();
        // uniformDirection = meshShader->GetDirectionLocation();
        // uniformCameraPosition = meshShader->GetCameraPositionLocation();
        // uniformSpecularIntensity = meshShader->GetSpecularIntensityLocation();
        // uniformSpecularShininess = meshShader->GetSpecularShininessLocation();

        // mainLight.UseLight(uniformAmbientIntensity, uniformAmbientColour, uniformDiffuseIntensity, uniformDirection);

        // glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        // glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
        // glUniform3f(uniformCameraPosition, camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

        // glm::mat4 model(1.0f);       
        // model = glm::translate(model, glm::vec3(0.0f, -.3, -2.0f));
        // model = glm::scale(model, glm::vec3(0.4f, 0.4f, 0.4f));

        // glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        // shinyMaterial.Use(uniformSpecularIntensity, uniformSpecularShininess);
        // brickTexture.UseTexture();

        // meshList[0] -> RenderMesh();

        // model = glm::mat4(1.0f);     
        // model = glm::translate(model, glm::vec3(0.0f, .3, -1.5f));
        // model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));

        // glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        // dullMaterial.Use(uniformSpecularIntensity, uniformSpecularShininess);
        // dirtTexture.UseTexture();

        // meshList[1] -> RenderMesh();

        GLfloat lineVertices[] = {
        //   x      y      z    
            0.0f, 0.0f, 0.0f,
            1.0f, 1.0f, 1.0f
        };

        Line *line = new Line();
        line -> Create(lineVertices, 2);

        glUseProgram(0);

        mainWindow.swapBuffers();
    }

    return 0;
}