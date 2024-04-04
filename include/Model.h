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
    void loadMaterials(const aiScene *scene);
    Texture* getTexture(unsigned int textureId, const aiScene *scene);

    std::vector<MeshObject *> _meshObjects;
    Transform _transform;
    ShaderMesh* _shaderMesh;
    Material _material;
    Texture* _default_texture;

    std::vector<Texture*> _textureList;
    std::vector<MeshRenderer*> _meshRendererList;
    std::vector<unsigned int> _meshToTex;
};