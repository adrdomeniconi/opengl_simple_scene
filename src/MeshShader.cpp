#include "MeshShader.h"

MeshShader::MeshShader(const char* vertexShaderLocation, const char* fragmentShaderLocation): uniformModel(0), uniformProjection(0), shader(Shader()), pointLightsCount(0), spotLightsCount(0), shaderID(0)
{
    shaderID = shader.CreateFromFiles(vertexShaderLocation, fragmentShaderLocation);
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

    getDirectionalLightUniformLocations();
    getPointLightUniformLocations();
    getSpotLightUniformLocations();
}

void MeshShader::getDirectionalLightUniformLocations()
{
    uniformDirectionalLight.ambientColour = glGetUniformLocation(shaderID, "directionalLight.light.colour");
    uniformDirectionalLight.ambientIntesity = glGetUniformLocation(shaderID, "directionalLight.light.ambientIntensity");
    uniformDirectionalLight.diffuseIntesity = glGetUniformLocation(shaderID, "directionalLight.light.diffuseIntensity");
    uniformDirectionalLight.direction = glGetUniformLocation(shaderID, "directionalLight.direction");
}

void MeshShader::getPointLightUniformLocations()
{
    for (size_t i = 0; i < MAX_POINT_LIGHTS_COUNT; i++)
    {
        uniformPointLights[i].ambientColour = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].light.colour").c_str());
        uniformPointLights[i].ambientIntesity = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].light.ambientIntensity").c_str());
        uniformPointLights[i].diffuseIntesity = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].light.diffuseIntensity").c_str());
        uniformPointLights[i].position = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].position").c_str());
        uniformPointLights[i].constant = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].constant").c_str());
        uniformPointLights[i].linear = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].linear").c_str());
        uniformPointLights[i].exponent = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].exponent").c_str());
    }
    uniformPointLightsCount = glGetUniformLocation(shaderID, "pointLightsCount");
}

void MeshShader::getSpotLightUniformLocations()
{
    for (size_t i = 0; i < MAX_SPOT_LIGHTS_COUNT; i++)
    {
        uniformSpotLights[i].ambientColour = glGetUniformLocation(shaderID, ("spotLights[" + std::to_string(i) + "].pointLight.light.colour").c_str());
        uniformSpotLights[i].ambientIntesity = glGetUniformLocation(shaderID, ("spotLights[" + std::to_string(i) + "].pointLight.light.ambientIntensity").c_str());
        uniformSpotLights[i].diffuseIntesity = glGetUniformLocation(shaderID, ("spotLights[" + std::to_string(i) + "].pointLight.light.diffuseIntensity").c_str());
        uniformSpotLights[i].position = glGetUniformLocation(shaderID, ("spotLights[" + std::to_string(i) + "].pointLight.position").c_str());
        uniformSpotLights[i].constant = glGetUniformLocation(shaderID, ("spotLights[" + std::to_string(i) + "].pointLight.constant").c_str());
        uniformSpotLights[i].linear = glGetUniformLocation(shaderID, ("spotLights[" + std::to_string(i) + "].pointLight.linear").c_str());
        uniformSpotLights[i].exponent = glGetUniformLocation(shaderID, ("spotLights[" + std::to_string(i) + "].pointLight.exponent").c_str());
        uniformSpotLights[i].direction = glGetUniformLocation(shaderID, ("spotLights[" + std::to_string(i) + "].direction").c_str());
        uniformSpotLights[i].coneAngle = glGetUniformLocation(shaderID, ("spotLights[" + std::to_string(i) + "].coneAngle").c_str());
    }
    uniformSpotLightsCount = glGetUniformLocation(shaderID, "pointLightsCount");
}

void MeshShader::UseShader()
{
    shader.UseShader();
}

void MeshShader::ClearShader()
{
    shader.ClearShader();
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

void MeshShader::SetPointLights(const std::vector<std::shared_ptr<PointLight>> &pointLights)
{
    if(pointLights.size() > MAX_POINT_LIGHTS_COUNT) 
        throw std::runtime_error("Max point light count reached. Cannot add nother point light.");
    
    unsigned int idx = 0;
    for(const std::shared_ptr<PointLight>& pointLight : pointLights)
    {
        pointLight->UseLight(uniformPointLights[idx].ambientIntesity, 
                            uniformPointLights[idx].ambientColour, 
                            uniformPointLights[idx].diffuseIntesity, 
                            uniformPointLights[idx].position, 
                            uniformPointLights[idx].constant, 
                            uniformPointLights[idx].linear, 
                            uniformPointLights[idx].exponent);
        ++idx;
    }
    

    pointLightsCount = pointLights.size();
    glUniform1i(uniformPointLightsCount, pointLightsCount);
}

void MeshShader::SetSpotLights(const std::vector<std::shared_ptr<SpotLight>> &spotLights)
{
    if(spotLights.size() > MAX_SPOT_LIGHTS_COUNT) 
        throw std::runtime_error("Max Spotlights count reached. Cannot add nother spotlight.");
    
    unsigned int idx = 0;
    for(const std::shared_ptr<SpotLight>& spotLight : spotLights)
    {
        spotLight->UseLight(uniformSpotLights[idx].ambientIntesity, 
                            uniformSpotLights[idx].ambientColour, 
                            uniformSpotLights[idx].diffuseIntesity, 
                            uniformSpotLights[idx].position, 
                            uniformSpotLights[idx].constant, 
                            uniformSpotLights[idx].linear, 
                            uniformSpotLights[idx].exponent,
                            uniformSpotLights[idx].direction,
                            uniformSpotLights[idx].coneAngle);
        ++idx;
    }
    
    spotLightsCount = spotLights.size();
    glUniform1i(uniformSpotLightsCount, spotLightsCount);
}

MeshShader::~MeshShader()
{
    ClearShader();
}
