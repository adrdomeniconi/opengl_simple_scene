#include "Scenes/SampleScene.h"

SampleScene::SampleScene(TextureLibrary* textureLibrary, MaterialLibrary* materialLibrary, ShaderLibrary* shaderLibrary) : 
    _textureLibrary(textureLibrary),
    _materialLibrary(materialLibrary),
    _shaderLibrary(shaderLibrary),
    _shaderMesh(dynamic_cast<ShaderMesh*>(shaderLibrary->GetShader(ShaderLibrary::ShaderType::Mesh)))
{  
    createObjects();
    createLights();
}

void SampleScene::createObjects()
{
    MeshObject pyramidA = MeshObject(createPyramidMesh(), _shaderMesh, _materialLibrary->GetMaterial(MaterialLibrary::MaterialType::Shiny), _textureLibrary->GetTexture(TextureLibrary::TextureType::Brick));
    pyramidA.Scale(0.4f, 0.4f, 0.4f);
    _objects.push_back(pyramidA);

    MeshObject pyramidB = MeshObject(createPyramidMesh(), _shaderMesh, _materialLibrary->GetMaterial(MaterialLibrary::MaterialType::Dull), _textureLibrary->GetTexture(TextureLibrary::TextureType::Dirt));
    pyramidB.Translate(0.0f, .3, -1.5f);
    pyramidB.Scale(0.2f, 0.2f, 0.2f);
    _objects.push_back(pyramidB);

    MeshObject floor = MeshObject(createFloorMesh(), _shaderMesh, _materialLibrary->GetMaterial(MaterialLibrary::MaterialType::Shiny), _textureLibrary->GetTexture(TextureLibrary::TextureType::Floor));
    floor.Translate(0.0f, -2.0f, 0.0f);
    _objects.push_back(floor);
}

void SampleScene::createLights()
{
    mainLight = DirectionalLight(0.0f, 1.0f, 0.0f, 0.2f, 0.5f, -1.0f, 1.5f, 0.4f);
    pointLights.push_back(PointLight(1.0f, 0.0f, 0.0f, 0.2f, 0.7f, 2.0f, 1.5f, 2.0f, 0.1f, 0.2f, 0.3f));
    spotLights.push_back(SpotLight(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.2f, 0.0f, 0.0f, -1.0f, 0.0f, 20));
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

void SampleScene::Update(Camera camera, glm::mat4 projection)
{
    spotLights[0].SetDirection(camera.GetDirection());
    spotLights[0].SetPosition(camera.GetPosition());

     //Configure the Mesh shader
    _shaderMesh->UseShader();
    _shaderMesh->SetDirectionalLight(mainLight);
    _shaderMesh->SetPointLights(pointLights);
    _shaderMesh->SetSpotLights(spotLights);

    glUniformMatrix4fv(_shaderMesh->GetProjectionLocation(), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(_shaderMesh->GetViewLocation(), 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
    glUniform3f(_shaderMesh->GetCameraPositionLocation(), camera.GetPosition().x, camera.GetPosition().y, camera.GetPosition().z);

    for(auto meshObject : _objects)
    {
        meshObject.Render();
    }
}

SampleScene::~SampleScene()
{
}