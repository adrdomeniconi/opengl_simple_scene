#pragma once

#include <vector>
#include <string>
#include <iostream>

#include "MeshObject.h"
#include "Transform.h"
#include "Shader.h"
#include "MeshRenderer.h"
#include "Material.h"

#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>

class Model 
{
public:

    Model(ShaderMesh* shaderMesh, Material material, Texture* default_texture);
    ~Model();

    bool Load(const std::string& filename);
    void Render();
    void Clear();

private:

    void loadNode(aiNode *node, const aiScene *scene);
    void loadMesh(aiMesh *mesh, const aiScene *scene);
    void getIndices(aiMesh *mesh, std::vector<unsigned int> &indices);
    void getVertices(aiMesh *mesh, std::vector<GLfloat> &vertices);
    void loadTexturesFromScene(const aiScene *scene);
    Texture* getTexture(unsigned int textureId);
    
    /* In this case the MeshObject lifetime should be attached to the Model lifetime.*/
    std::vector<std::unique_ptr<MeshObject>> _meshObjects;

    /* It's a unique pointer because I'm assuming that all the textures loaded from the model file are unique to the model, so that it should have its ownership.*/
    std::vector<std::unique_ptr<Texture>> _textures;

    Transform _transform;
    ShaderMesh* _shaderMesh;
    Material _material;
    Texture* _default_texture;
};