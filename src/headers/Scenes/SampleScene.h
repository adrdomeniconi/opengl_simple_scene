#pragma once

#include <vector>

#include "MeshObject.h"
#include "AverageNormalsCalculator.h"
#include "Shader.h"
#include "ShaderLine.h"
#include "Texture.h"
#include "TextureLibrary.h"
#include "MaterialLibrary.h"
#include "ShaderLibrary.h"
#include "Mesh.h"

class SampleScene
{
    
public:
    SampleScene();


    std::vector<MeshObject> GetStageObjects();
    MeshObject& GetStageObjects(unsigned int index);

    ~SampleScene();

    ShaderLibrary shaderLibrary;

private:
    TextureLibrary _textureLibrary;
    MaterialLibrary _materialLibrary;
    std::vector<MeshObject> _objects;

    // DirectionalLight mainLight;
    // std::vector<std::shared_ptr<PointLight>> pointLights;
    // std::vector<std::shared_ptr<SpotLight>> spotLights;

    Mesh* createFloorMesh();
    Mesh* createPyramidMesh();
    void createObjects();

};