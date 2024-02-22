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
    pointLightsCount = 0;
}

void MeshShader::getDirectionalLightUniformLocations(GLuint shaderID)
{
    uniformDirectionalLight.ambientColour = glGetUniformLocation(shaderID, "directionalLight.base.colour");
    uniformDirectionalLight.ambientIntesity = glGetUniformLocation(shaderID, "directionalLight.base.ambientIntensity");
    uniformDirectionalLight.diffuseIntesity = glGetUniformLocation(shaderID, "directionalLight.base.diffuseIntensity");
    uniformDirectionalLight.direction = glGetUniformLocation(shaderID, "directionalLight.direction");
}

void MeshShader::getPointLightUniformLocations(GLuint shaderID)
{
    for (size_t i = 0; i < MAX_POINT_LIGHTS_COUNT; i++)
    {
        uniformPointLight[i].ambientColour = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].base.colour").c_str());
        uniformPointLight[i].ambientIntesity = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].base.ambientIntensity").c_str());
        uniformPointLight[i].diffuseIntesity = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].base.diffuseIntensity").c_str());
        uniformPointLight[i].position = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].position").c_str());
        uniformPointLight[i].constant = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].constant").c_str());
        uniformPointLight[i].linear = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].linear").c_str());
        uniformPointLight[i].exponent = glGetUniformLocation(shaderID, ("pointLights[" + std::to_string(i) + "].exponent").c_str());
    }
    uniformPointLightsCount = glGetUniformLocation(shaderID, "pointLightsCount");

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

void MeshShader::SetPointLights(const std::vector<PointLight*>& pointLights)
{
    if(pointLights.size() > MAX_POINT_LIGHTS_COUNT) 
        throw std::runtime_error("Max point light count reached. Cannot add nother point light.");
    
    unsigned int idx = 0;
    for(const PointLight* pointLight : pointLights)
    {
        pointLight->UseLight(uniformPointLight[idx].ambientIntesity, 
                            uniformPointLight[idx].ambientColour, 
                            uniformPointLight[idx].diffuseIntesity, 
                            uniformPointLight[idx].position, 
                            uniformPointLight[idx].constant, 
                            uniformPointLight[idx].linear, 
                            uniformPointLight[idx].exponent);
        ++idx;
    }
    

    pointLightsCount = pointLights.size();
    glUniform1i(uniformPointLightsCount, pointLightsCount);
}

MeshShader::~MeshShader()
{
    ClearShader();
}
