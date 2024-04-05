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

bool Model::Load(const std::string &filename, const std::string &texturesPath)
{
    Assimp::Importer importer;
    if(!std::filesystem::exists(filename))
    {
        std::cout << "*ERROR*: Model file not found: " << filename << std::endl;
        return false;
    }

    const aiScene *scene = importer.ReadFile(filename, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenSmoothNormals | aiProcess_JoinIdenticalVertices);

    if (!scene)
    {
        std::cout << "*ERROR*: Loading the model (" << filename << "): " << importer.GetErrorString();
        return false;
    }

    loadTexturesFromScene(scene, texturesPath);
    loadNode(scene-> mRootNode, scene);

    std::cout << "Number of nodes " << scene->mRootNode->mNumMeshes << std::endl;

    return true;
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

void Model::Translate(GLfloat x, GLfloat y, GLfloat z)
{
    _transform.Translate(x, y, z);
}

void Model::Rotate(GLfloat x, GLfloat y, GLfloat z)
{
    _transform.Rotate(x, y, z);
}

void Model::Scale(GLfloat x, GLfloat y, GLfloat z)
{
    _transform.Scale(x, y, z);
}

glm::vec3 Model::Translation()
{
    return _transform.Translation();
}

glm::vec3 Model::Rotation()
{
    return _transform.Rotation();
}

glm::vec3 Model::Scale()
{
    return _transform.Scale();
}

void Model::loadNode(aiNode *node, const aiScene *scene)
{
    std::cout << "Loading "<< node->mName.C_Str() << " node. Number of meshes: " << node->mNumMeshes << std::endl;

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
    std::cout << "Loading "<< mesh->mName.C_Str() << " mesh..." << std::endl;

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
        std::cout << "Texture not found for " << mesh->mName.C_Str() << ". Applying default texture..." << std::endl;
        texture = _default_texture;
    }

    auto meshObject = std::make_unique<MeshObject>(std::move(meshRenderer), _shaderMesh, _material, texture, _transform.Model());
    _meshObjects.push_back(std::move(meshObject));
}

void Model::getIndices(aiMesh *mesh, std::vector<unsigned int> &indices)
{
    // std::cout << "Getting indices of " << mesh->mName.C_Str() << std::endl;
    // std::cout << "mNumFaces:" << mesh->mNumFaces << std::endl;

    for (size_t i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; j++)
        {
            indices.push_back(face.mIndices[j]);
        }
    }
}

void Model::getVertices(aiMesh *mesh, std::vector<GLfloat> &vertices)
{
    // std::cout << "Getting vertices of " << mesh->mName.C_Str() << std::endl;
    // std::cout << "mNumVertices:" << mesh->mNumVertices << std::endl;

    for (size_t i = 0; i < mesh->mNumVertices; i++)
    {
        vertices.insert(vertices.end(), {mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
        // std::cout << "Inserting " << mesh->mVertices[i].x << ", " << mesh->mVertices[i].y << ", " << mesh->mVertices[i].z << std::endl;

        if (mesh->mTextureCoords[0])
        {
            vertices.insert(vertices.end(), {mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y});
            // std::cout << "Inserting " << mesh->mTextureCoords[0][i].x << ", " << mesh->mTextureCoords[0][i].y << std::endl;
        }
        else
        {
            vertices.insert(vertices.end(), {0.0f, 0.0f});
            // std::cout << "Inserting default 0.0f values" << std::endl;
        }

        vertices.insert(vertices.end(), {mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z});
        // std::cout << "Inserting " << mesh->mNormals[i].x << ", " << mesh->mNormals[i].y << ", " << mesh->mNormals[i].z << std::endl;
    }

    // std::cout << "Final size " << vertices.size() << std::endl;
}

void Model::loadTexturesFromScene(const aiScene *scene, const std::string &texturesPath)
{
    _textures.resize(scene->mNumMaterials);
    std::cout << "Number of materials: " << scene->mNumMaterials << std::endl;

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

                std::string texturePath = texturesPath + "/" + filename;
                if (std::filesystem::exists(texturePath)) 
                {
                    _textures[textureId] = std::make_unique<Texture>(texturePath.c_str());
                    std::cout << "Found texture (" << texturePath << ") for id: " << textureId << std::endl;
                } 
                else
                {
                    std::cout << "*ERROR*: The file " << texturePath << " does not exist.\n";
                }

            } 
            else 
            {
                std::cout << "*ERROR*: Loading texture id (" << textureId << ")." << std::endl;
            }
        }
        else 
        {
            std::cout << "*WARNING*: Texture not found for id (" << textureId << ")." << std::endl;
        }
    }
}

Texture* Model::getTexture(unsigned int textureId)
{
    // std::cout << "Get texture(" << textureId << ")" << std::endl;
    // std::cout << "_textures.size()" << _textures.size() << std::endl;

    if(textureId < _textures.size())
    {
        return _textures[textureId].get();
    }

    return nullptr;
}


