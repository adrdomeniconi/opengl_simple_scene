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

class SampleScene
{
    
public:

    SampleScene();

    std::vector<MeshObject> GetStageObjects();

    ~SampleScene();

    TextureLibrary textureLibrary;
    MaterialLibrary materialLibrary;
    ShaderLibrary shaderLibrary;

private:
    std::vector<MeshObject> _objects;
    std::vector<Light> _lights;
    std::vector<Shader> _shaders;
    std::vector<Texture> _textures;

    //TODO: Temporary variables (POC)
    // ShaderMesh *meshShader;
    // ShaderLine *lineShader;

    // DirectionalLight mainLight;
    // std::vector<std::shared_ptr<PointLight>> pointLights;
    // std::vector<std::shared_ptr<SpotLight>> spotLights;
    
    // Material shinyMaterial;
    // Material dullMaterial;
    //

    void createFloor();
    void createPyramid();

};