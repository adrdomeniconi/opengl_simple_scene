#pragma once

#include <vector>

#include "MeshObject.h"
#include "AverageNormalsCalculator.h"
#include "Shader.h"
#include "ShaderLine.h"
#include "Texture.h"
#include "TextureLibrary.h"
#include "MaterialLibrary.h"

//TODO: Temp solution
inline constexpr const char* VERTEX_SHADER_FILE = "Shaders/shader.vert";
inline constexpr const char* FRAGMENT_SHADER_FILE = "Shaders/shader.frag";
inline constexpr const char* VERTEX_SHADER_LINE_FILE = "Shaders/line_shader.vert";
inline constexpr const char* FRAGMENT_SHADER_LINE_FILE = "Shaders/line_shader.frag";

class SampleScene
{
    
public:

    SampleScene();

    std::vector<MeshObject> GetStageObjects();

    ~SampleScene();

    TextureLibrary textureLibrary;
    MaterialLibrary materialLibrary;

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