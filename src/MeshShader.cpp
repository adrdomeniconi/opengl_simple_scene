#include "MeshShader.h"

MeshShader::MeshShader(const char* vertexShaderLocation, const char* fragmentShaderLocation): uniformModel(0), uniformProjection(0), shader(Shader())
{
    GLuint shaderID = shader.CreateFromFiles(vertexShaderLocation, fragmentShaderLocation);
    if(shaderID == 0)
    {
        throw std::runtime_error("Error creating shader.");
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformAmbientColour = glGetUniformLocation(shaderID, "directionalLight.colour");
    uniformAmbientIntesity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
    uniformDiffuseIntesity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity");
    uniformDirection = glGetUniformLocation(shaderID, "directionalLight.direction");
    uniformCameraPosition = glGetUniformLocation(shaderID, "cameraPosition");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformSpecularShininess = glGetUniformLocation(shaderID, "material.shininess");
}

void MeshShader::UseShader()
{
    shader.UseShader();
}

void MeshShader::ClearShader()
{
    shader.ClearShader();
    uniformModel = 0;
    uniformProjection = 0;
}

GLuint MeshShader::GetProjectionLocation() { return uniformProjection; }

GLuint MeshShader::GetModelLocation() { return uniformModel; }

GLuint MeshShader::GetViewLocation() { return uniformView; }

GLuint MeshShader::GetAmbientIntensityLocation() { return uniformAmbientIntesity; }

GLuint MeshShader::GetAmbientColourLocation() { return uniformAmbientColour; }

GLuint MeshShader::GetDiffuseIntensityLocation()  { return uniformDiffuseIntesity; }

GLuint MeshShader::GetDirectionLocation()  { return uniformDirection; }

GLuint MeshShader::GetCameraPositionLocation() { return uniformCameraPosition; }

GLuint MeshShader::GetSpecularIntensityLocation() { return uniformSpecularIntensity; }

GLuint MeshShader::GetSpecularShininessLocation() { return uniformSpecularShininess; }

MeshShader::~MeshShader()
{
    ClearShader();
}
