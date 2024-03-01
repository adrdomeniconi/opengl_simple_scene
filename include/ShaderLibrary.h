#pragma once

#include <map>

#include "Shader.h"
#include "ShaderLine.h"
#include "ShaderMesh.h"

inline constexpr const char* VERTEX_SHADER_FILE = "../resources/shaders/shader.vert";
inline constexpr const char* FRAGMENT_SHADER_FILE = "../resources/shaders/shader.frag";
inline constexpr const char* VERTEX_SHADER_LINE_FILE = "../resources/shaders/line_shader.vert";
inline constexpr const char* FRAGMENT_SHADER_LINE_FILE = "../resources/shaders/line_shader.frag";

class ShaderLibrary
{
public:
    enum class ShaderType
    {
        Line,
        Mesh
    };

    ShaderLibrary();
    Shader* GetShader(ShaderType type);
    ~ShaderLibrary();

private:
    std::map<ShaderType, Shader*> _shaders;
};