#include "ShaderLibrary.h"

ShaderLibrary::ShaderLibrary()
{
    _shaders[ShaderType::Line] = new ShaderLine(VERTEX_SHADER_LINE_FILE, FRAGMENT_SHADER_LINE_FILE);
    _shaders[ShaderType::Mesh] = new ShaderMesh(VERTEX_SHADER_FILE, FRAGMENT_SHADER_FILE);
}

Shader *ShaderLibrary::GetShader(ShaderType type)
{
    return _shaders.at(type);
}

ShaderLibrary::~ShaderLibrary()
{
    for(auto shaderPair : _shaders)
    {
        delete(shaderPair.second);
    }
}
