#pragma once

#include <vector>
#include <GLM/glm.hpp>

#include "MeshObject.h"
#include "AverageNormalsCalculator.h"
#include "Shader.h"
#include "ShaderLine.h"
#include "ShaderMesh.h"
#include "Texture.h"
#include "TextureLibrary.h"
#include "MaterialLibrary.h"
#include "ShaderLibrary.h"
#include "Mesh.h"
#include "Camera.h"

class SampleScene
{
    
public:
    SampleScene();

    std::vector<MeshObject> GetStageObjects();

    MeshObject& GetStageObjects(unsigned int index);
    void Update(Camera camera, glm::mat4 projection);

    ~SampleScene();

    ShaderLibrary shaderLibrary;
    DirectionalLight mainLight;
    std::vector<PointLight> pointLights;
    std::vector<SpotLight> spotLights;

private:
    TextureLibrary _textureLibrary;
    MaterialLibrary _materialLibrary;
    std::vector<MeshObject> _objects;
    ShaderMesh* _shaderMesh; 


    Mesh* createFloorMesh();
    Mesh* createPyramidMesh();
    void createObjects();

};