#include <graphics/Shader.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor
Shader::Shader(const std::string& _vertexSource, const std::string& _fragmentSource, const std::string& _tessControlSource, const std::string& _tessEvaluationSource)
{
    // Read Shader files
    std::string vertexSource = ReadFile(_vertexSource);
    std::string fragmentSource = ReadFile(_fragmentSource);
    std::string tessControlSource = ReadFile(_tessControlSource);
    std::string tessEvaluationSource = ReadFile(_tessEvaluationSource);

    // Compile shaders
    GLuint vertexShader = CompileShader(GL_VERTEX_SHADER, vertexSource);
    GLuint fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentSource);
    GLuint tessControlShader = CompileShader(GL_TESS_CONTROL_SHADER, tessControlSource);
    GLuint tessEvaluationShader = CompileShader(GL_TESS_EVALUATION_SHADER, tessEvaluationSource);

    // Create shader program
    programID = glCreateProgram();

    // Attach Shaders
    glAttachShader(programID, vertexShader);
    glAttachShader(programID, fragmentShader);
    glAttachShader(programID, tessControlShader);
    glAttachShader(programID, tessEvaluationShader);

    // Link programs
    glLinkProgram(programID);

    // Check errors
    CheckCompileErrors(programID, "PROGRAM");

    // Delete Shaders
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glDeleteShader(tessControlShader);
    glDeleteShader(tessEvaluationShader);
}
Shader::~Shader()
{
    glDeleteProgram(programID);
}

void Shader::Use() const
{
    glUseProgram(programID);
}

GLuint Shader::GetProgramID()
{
    return programID;
}

// Setters
void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(GetUniformLocation(name), value);
}

void Shader::SetVec3(const std::string& name, float x, float y, float z) const
{
    glUniform3f(GetUniformLocation(name), x, y, z);
}

void Shader::SetMat4(const std::string& name, const float* matrix) const
{
    glUniformMatrix4fv(
        GetUniformLocation(name),
        1,
        GL_FALSE,
        matrix
    );
}

std::string Shader::ReadFile(const std::string& filepath)
{
    std::ifstream file(filepath);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

GLuint Shader::CompileShader(GLenum type, const std::string& source)
{
    GLuint shader = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    CheckCompileErrors(shader, "SHADER");
    return shader;
}

void Shader::CheckCompileErrors(GLuint object, const std::string& type)
{
    int success;
    char infoLog[1024];

    if (type == "SHADER")
    {
        glGetShaderiv(object, GL_COMPILE_STATUS, &success);

        if (!success)
        {
            glGetShaderInfoLog(object, 1024, nullptr, infoLog);

            std::cout << "Shader Compilation Error : \n";
            std::cout << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(object, GL_LINK_STATUS, &success);

        if(!success)
        {
            glGetProgramInfoLog(object, 1024, nullptr, infoLog);

            std::cout << "Program Linking Error:\n";
            std::cout << infoLog << std::endl;
        }
    }
}

GLint Shader::GetUniformLocation(const std::string& name) const
{
    if (UniformCache.find(name) != UniformCache.end())
    {
        return UniformCache[name];
    }
    
    GLint location = glGetUniformLocation(programID, name.c_str());

    UniformCache[name] = location;

    return location;
}