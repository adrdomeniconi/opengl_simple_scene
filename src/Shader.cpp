#include <Shader.h>

Shader::Shader()
{
    shaderID = 0;
}

GLuint Shader::CreateFromString(const char* vertexCode, const char* fragmentCode)
{
    return CompileShader(vertexCode, fragmentCode);
}

GLuint Shader::CreateFromFiles(const char* vertexLocation, const char* fragmentLocation)
{
    std::string vertexString = ReadFile(vertexLocation);
    std::string fragmentString = ReadFile(fragmentLocation);

    const char* vertexCode = vertexString.c_str();
    const char* fragmentCode = fragmentString.c_str();

    return CompileShader(vertexCode, fragmentCode);
}

std::string Shader::ReadFile(const char* fileLocation)
{
    std::string content;
    std::ifstream fileStream(fileLocation, std::ios::in);

    if(!fileStream.is_open()) {
        printf("Failed to read %s!", fileLocation);
        return "";
    }

    std::string line = "";
    while (!fileStream.eof())
    {
        std::getline(fileStream, line);
        content.append(line + "\n");
    }

    fileStream.close();

    return content;
}

GLuint Shader::CompileShader(const char* vertexCode, const char* fragmentCode)
{
    shaderID = glCreateProgram();
    if(!shaderID) {
        printf("Error creating shader program.\n");
        return 0;
    }

    AddShader(shaderID, vertexCode, GL_VERTEX_SHADER);
    AddShader(shaderID, fragmentCode, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = { 0 }; 

    //Create the executable on the graphics card
    glLinkProgram(shaderID);
    glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
    if(!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error linking program: '%s'\n", eLog);
        return 0;
    }

    //Just validate if it worked
    glValidateProgram(shaderID);
    glGetProgramiv(shaderID, GL_VALIDATE_STATUS, &result);
    if(!result)
    {
        glGetProgramInfoLog(shaderID, sizeof(eLog), NULL, eLog);
        printf("Error validating program: '%s'\n", eLog);
    }

    return shaderID;
}


void Shader::UseShader()
{
    glUseProgram(shaderID);
}

void Shader::ClearShader()
{
    if(shaderID != 0)
    {
        glDeleteProgram(shaderID);
        shaderID = 0;
    }

}

void Shader::AddShader(GLuint program, const char* shaderCode, GLenum shaderType)
{
    GLuint shader = glCreateShader(shaderType);

    //Get and compile the shader code
    const GLchar* code[1];
    code[0] = shaderCode;

    GLint codeLength[1];
    codeLength[0] = strlen(shaderCode);

    glShaderSource(shader, 1, code, codeLength);
    glCompileShader(shader);

    GLint result = 0;
    GLchar eLog[1024] = { 0 }; 

    glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
    if(!result)
    {
        glGetShaderInfoLog(shader, sizeof(eLog), NULL, eLog);
        printf("Error compiling the %d shader: '%s'\n", shaderType, eLog);
        return;
    }

    //Attach the compiled shader to the program
    glAttachShader(program, shader);
}

Shader::~Shader()
{
    ClearShader();
}
