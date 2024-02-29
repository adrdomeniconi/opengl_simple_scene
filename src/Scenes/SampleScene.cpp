#include "Scenes/SampleScene.h"

SampleScene::SampleScene() : 
    _textureLibrary(TextureLibrary()),
    _materialLibrary(MaterialLibrary()),
    shaderLibrary(ShaderLibrary())
{  
    createObjects();
}

void SampleScene::createObjects()
{
    ShaderMesh* meshShader = dynamic_cast<ShaderMesh*>(shaderLibrary.GetShader(ShaderLibrary::ShaderType::Mesh));

    MeshObject pyramidA = MeshObject(createPyramidMesh(), meshShader, _materialLibrary.GetMaterial(MaterialLibrary::MaterialType::Shiny), _textureLibrary.GetTexture(TextureLibrary::TextureType::Brick));
    pyramidA.Scale(0.4f, 0.4f, 0.4f);
    _objects.push_back(pyramidA);

    MeshObject pyramidB = MeshObject(createPyramidMesh(), meshShader, _materialLibrary.GetMaterial(MaterialLibrary::MaterialType::Dull), _textureLibrary.GetTexture(TextureLibrary::TextureType::Dirt));
    pyramidB.Translate(0.0f, .3, -1.5f);
    pyramidB.Scale(0.2f, 0.2f, 0.2f);
    _objects.push_back(pyramidB);

    MeshObject floor = MeshObject(createFloorMesh(), meshShader, _materialLibrary.GetMaterial(MaterialLibrary::MaterialType::Shiny), _textureLibrary.GetTexture(TextureLibrary::TextureType::Floor));
    floor.Translate(0.0f, -2.0f, 0.0f);
    _objects.push_back(floor);
}
std::vector<MeshObject> SampleScene::GetStageObjects()
{
    return _objects;
}

MeshObject& SampleScene::GetStageObjects(unsigned int index)
{
    return _objects[index];
}

Mesh *SampleScene::createPyramidMesh()
{
    unsigned int indices[] = {
        4, 1, 0,
        4, 2, 1,
        4, 3, 2,
        4, 0, 3
    };

    GLfloat vertices[] = {
    //    x      y      z     u     v     nx    ny    nz
        -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
        -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
         0.0f,  1.0f,  0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
    };

    const unsigned int indicesCount = sizeof(indices)/sizeof(indices[0]);
    const unsigned int verticesDataCount = sizeof(vertices)/sizeof(vertices[0]);
    const unsigned int VERTEX_LENGTH = 8;
    const unsigned int NORMALS_OFFSET = 5;
    const unsigned int verticesCount = verticesDataCount/VERTEX_LENGTH;

    AverageNormalsCalculator::Calculate(indices, indicesCount, vertices, verticesDataCount, VERTEX_LENGTH, NORMALS_OFFSET);

    Mesh *mesh = new Mesh();
    mesh->CreateMesh(vertices, indices, verticesDataCount, indicesCount, VERTEX_LENGTH, NORMALS_OFFSET);

    return mesh;
}

Mesh* SampleScene::createFloorMesh()
{
    unsigned int indices[] = {
        0, 1, 3,
        3, 1, 2 
    };

    GLfloat vertices[] = {
    //    x      y      z     u     v     nx    ny    nz
        -10.0f, 0.0f, -10.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
        -10.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
        10.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
        10.0f, 0.0f, -10.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
    };

    const unsigned int indicesCount = sizeof(indices)/sizeof(GLfloat);
    const unsigned int verticesDataCount = sizeof(vertices)/sizeof(unsigned int);

    Mesh *mesh = new Mesh();
    mesh -> CreateMesh(vertices, indices, verticesDataCount, indicesCount, 8, 5);

    return mesh;
}

SampleScene::~SampleScene()
{
}