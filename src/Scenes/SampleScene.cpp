#include "Scenes/SampleScene.h"

SampleScene::SampleScene() : textureLibrary(TextureLibrary())
{   
    //TODO: Should be transfer to a ShaderFactory
    // meshShader = new ShaderMesh(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
    // lineShader = new ShaderLine(VERTEX_SHADER_LINE_FILE, FRAGMENT_SHADER_LINE_FILE);

    // mainLight = DirectionalLight(0.0f, 1.0f, 0.0f, 0.2f, 0.5f, -1.0f, 1.5f, 0.4f);

    // auto pointLight1 = std::make_shared<PointLight>(1.0f, 0.0f, 0.0f, 0.2f, 0.7f, 2.0f, 1.5f, 2.0f, 0.1f, 0.2f, 0.3f);
    // pointLights.push_back(pointLight1);

    // auto cameraSpotLight = std::make_shared<SpotLight>(1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.1f, 0.2f, 0.0f, 0.0f, -1.0f, 0.0f, 20);
    // spotLights.push_back(cameraSpotLight);

    // shinyMaterial = Material(4.0f, 256);
    // dullMaterial = Material(0.3f, 4);

    // MeshObject pyramidA = MeshObject(meshList[0], meshShader, shinyMaterial, &brickTexture);
    // MeshObject pyramidB = MeshObject(meshList[1], meshShader, dullMaterial, &dirtTexture);
    // MeshObject floorMesh = MeshObject(meshList[2], meshShader, shinyMaterial, &dirtTexture);
}

std::vector<MeshObject> SampleScene::GetStageObjects()
{
    return std::vector<MeshObject>();
}

// void SampleScene::createPyramid()
// {
//     unsigned int indices[] = {
//         4, 1, 0,
//         4, 2, 1,
//         4, 3, 2,
//         4, 0, 3
//     };

//     GLfloat vertices[] = {
//     //    x      y      z     u     v     nx    ny    nz
//         -1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//          1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//          1.0f, -1.0f,  1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//         -1.0f, -1.0f,  1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
//          0.0f,  1.0f,  0.0f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f
//     };

//     const unsigned int indicesCount = sizeof(indices)/sizeof(indices[0]);
//     const unsigned int verticesDataCount = sizeof(vertices)/sizeof(vertices[0]);
//     const unsigned int VERTEX_LENGTH = 8;
//     const unsigned int NORMALS_OFFSET = 5;
//     const unsigned int verticesCount = verticesDataCount/VERTEX_LENGTH;

//     AverageNormalsCalculator::Calculate(indices, indicesCount, vertices, verticesDataCount, VERTEX_LENGTH, NORMALS_OFFSET);

//     Mesh *mesh = new Mesh();
//     mesh->CreateMesh(vertices, indices, verticesDataCount, indicesCount, VERTEX_LENGTH, NORMALS_OFFSET);

//     _objects.push_back(mesh);
// }

// void SampleScene::createFloor()
// {
//     unsigned int indices[] = {
//         0, 1, 3,
//         3, 1, 2 
//     };

//     GLfloat vertices[] = {
//     //    x      y      z     u     v     nx    ny    nz
//         -10.0f, 0.0f, -10.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
//         -10.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 
//         10.0f, 0.0f, 10.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
//         10.0f, 0.0f, -10.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 
//     };

//     const unsigned int indicesCount = sizeof(indices)/sizeof(GLfloat);
//     const unsigned int verticesDataCount = sizeof(vertices)/sizeof(unsigned int);

//     Mesh *mesh = new Mesh();
//     mesh -> CreateMesh(vertices, indices, verticesDataCount, indicesCount, 8, 5);
//     meshList.push_back(mesh);
// }

SampleScene::~SampleScene()
{
}