#include "Model.h"

Model::Model(ShaderMesh* shaderMesh, Material material, Texture* default_texture) :
    _shaderMesh(shaderMesh),
    _material(material),
    _transform(Transform()),
    _default_texture(default_texture)
{
    //Do nothing.
}

Model::~Model()
{
    Clear();
}

bool Model::Load(const std::string &filename)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (!scene)
    {
        std::cout << "Error loading the model (" << filename << "): " << importer.GetErrorString();
        return;
    }

    loadNode(scene-> mRootNode, scene);
    loadTexturesFromScene(scene);
}

void Model::Render()
{
    for(auto& meshObject : _meshObjects)
    {
        meshObject->Render();
    }
}

void Model::Clear()
{
}

void Model::loadNode(aiNode *node, const aiScene *scene)
{
    for (size_t i = 0; i < node->mNumMeshes ; i++)
    {
        int meshId = node->mMeshes[i];
        aiMesh* mesh = scene->mMeshes[meshId];
        loadMesh(mesh, scene);
    }

    for (size_t i = 0; i < node->mNumChildren; i++)
    {
        loadNode(node->mChildren[i], scene);
    }
}

void Model::loadMesh(aiMesh *mesh, const aiScene *scene)
{
    std::vector<GLfloat> vertices;
    std::vector<unsigned int> indices;

    getVertices(mesh, vertices);
    getIndices(mesh, indices);
    
    //    x      y      z     u     v     nx    ny    nz
    const unsigned int VERTEX_LENGTH = 8;
    const unsigned int NORMALS_OFFSET = 5;

    auto meshRenderer = std::make_unique<MeshRenderer>();
    meshRenderer->CreateMesh(&vertices[0], &indices[0], vertices.size(), indices.size(), VERTEX_LENGTH, NORMALS_OFFSET);

    Texture* texture = getTexture(mesh->mMaterialIndex);
    if(!texture)
    {
        texture = _default_texture;
    }

    auto meshObject = std::make_unique<MeshObject>(std::move(meshRenderer), _shaderMesh, _material, texture);
    _meshObjects.push_back(meshObject);
}

void Model::getIndices(aiMesh *mesh, std::vector<unsigned int> &indices)
{
    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; i < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
}

void Model::getVertices(aiMesh *mesh, std::vector<GLfloat> &vertices)
{
    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});

        if (mesh->mTextureCoords[0])
        {
            vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
        }
        else
        {
            vertices.insert(vertices.end(), {0.0f, 0.0f});
        }

        vertices.insert(vertices.end(), {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z});
    }
}

void Model::loadTexturesFromScene(const aiScene *scene)
{
    _textures.resize(scene->mNumMaterials);

    for (size_t textureId = 0; textureId < scene->mNumMaterials; textureId++)
    {
        aiMaterial* mMaterial = scene->mMaterials[textureId];
        _textures[textureId] = nullptr;

        if (mMaterial->GetTextureCount(aiTextureType_DIFFUSE))
        {
            aiString path;
            if (mMaterial->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            {
                int idx = std::string(path.data).rfind("\\");
                std::string filename = std::string(path.data).substr(idx + 1);

                std::string texturePath = std::string("Textures/") + filename;

                _textures[textureId] = std::make_unique<Texture>(texturePath.c_str());
            } 
            else 
            {
                std::cout << "Error loading texture id (" << textureId << "). Loading default texture." << std::endl;
            }
        }
        else 
        {
            std::cout << "Texture not found for id (" << textureId << "). Loading default texture." << std::endl;
        }
    }
}

Texture* Model::getTexture(unsigned int textureId)
{
    if(textureId < _textures.size())
    {
        return _textures[textureId].get();
    }

    return nullptr;
}
