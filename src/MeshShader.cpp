#include "MeshShader.h"

MeshShader::MeshShader(const char* vertexShaderLocation, const char* fragmentShaderLocation): uniformModel(0), uniformProjection(0), shader(Shader()), pointLightsCount(0)
{
    GLuint shaderID = shader.CreateFromFiles(vertexShaderLocation, fragmentShaderLocation);
    if(shaderID == 0)
    {
        throw std::runtime_error("Error creating shader.");
    }

    uniformModel = glGetUniformLocation(shaderID, "model");
    uniformProjection = glGetUniformLocation(shaderID, "projection");
    uniformView = glGetUniformLocation(shaderID, "view");
    uniformCameraPosition = glGetUniformLocation(shaderID, "cameraPosition");
    uniformSpecularIntensity = glGetUniformLocation(shaderID, "material.specularIntensity");
    uniformSpecularShininess = glGetUniformLocation(shaderID, "material.shininess");

    getDirectionalLightUniformLocations(shaderID);
    getPointLightUniformLocations(shaderID);
}

void MeshShader::getDirectionalLightUniformLocations(GLuint shaderID)
{
    uniformDirectionalLight.ambientColour = glGetUniformLocation(shaderID, "directionalLight.colour");
    uniformDirectionalLight.ambientIntesity = glGetUniformLocation(shaderID, "directionalLight.ambientIntensity");
    uniformDirectionalLight.diffuseIntesity = glGetUniformLocation(shaderID, "directionalLight.diffuseIntensity");
    uniformDirectionalLight.direction = glGetUniformLocation(shaderID, "directionalLight.direction");
}

void MeshShader::getPointLightUniformLocations(GLuint shaderID)
{
    for (size_t i = 0; i < MAX_POINT_LIGHTS_COUNT; i++)
    {
        uniformPointLight[i].ambientColour = glGetUniformLocation(shaderID, ("pointLight[" + std::to_string(i) + "].base.colour").c_str());
        uniformPointLight[i].ambientIntesity = glGetUniformLocation(shaderID, ("pointLight[" + std::to_string(i) + "].base.ambientIntensity").c_str());
        uniformPointLight[i].diffuseIntesity = glGetUniformLocation(shaderID, ("pointLight[" + std::to_string(i) + "].base.diffuseIntensity").c_str());
        uniformPointLight[i].position = glGetUniformLocation(shaderID, ("pointLight[" + std::to_string(i) + "].base.position").c_str());
        uniformPointLight[i].constant = glGetUniformLocation(shaderID, ("pointLight[" + std::to_string(i) + "].base.constant").c_str());
        uniformPointLight[i].linear = glGetUniformLocation(shaderID, ("pointLight[" + std::to_string(i) + "].base.linear").c_str());
        uniformPointLight[i].exponent = glGetUniformLocation(shaderID, ("pointLight[" + std::to_string(i) + "].base.exponent").c_str());
    }
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

GLuint MeshShader::GetCameraPositionLocation() { return uniformCameraPosition; }

GLuint MeshShader::GetSpecularIntensityLocation() { return uniformSpecularIntensity; }

GLuint MeshShader::GetSpecularShininessLocation() { return uniformSpecularShininess; }

void MeshShader::SetDirectionalLight(DirectionalLight *directionalLight)
{
    directionalLight->UseLight(uniformDirectionalLight.ambientIntesity, uniformDirectionalLight.ambientColour, uniformDirectionalLight.diffuseIntesity, uniformDirectionalLight.direction);
}

void MeshShader::AddPointLight(PointLight *pointLight)
{
    if(pointLightsCount >= MAX_POINT_LIGHTS_COUNT) 
        throw std::runtime_error("Max point light count reached. Cannot add nother point light.");
    
    
    pointLight->UseLight(uniformPointLight[pointLightsCount].ambientIntesity, 
                         uniformPointLight[pointLightsCount].ambientColour, 
                         uniformPointLight[pointLightsCount].diffuseIntesity, 
                         uniformPointLight[pointLightsCount].position, 
                         uniformPointLight[pointLightsCount].constant, 
                         uniformPointLight[pointLightsCount].linear, 
                         uniformPointLight[pointLightsCount].exponent);

    pointLightsCount++;
}

MeshShader::~MeshShader()
{
    ClearShader();
}
