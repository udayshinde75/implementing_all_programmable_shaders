#pragma once

#include <string>
#include <unordered_map>
#include <glad/include/glad/glad.h>

class Shader
{
    private:
        GLuint programID;
        mutable std::unordered_map<std::string, GLint> UniformCache;

    public:
        Shader(const std::string& vertexSource, const std::string& fragmentSource);
        ~Shader();

        void Use() const;
        GLuint GetProgramID();

        // Setters
        void SetInt(const std::string& name, int value) const;
        void SetFloat(const std::string& name, float value) const;
        void SetVec3(const std::string& name, float x, float y, float z) const;
        void SetMat4(const std::string& name, const float* matrix) const;

        private: //helpers
        std::string& ReadFile(const std::string& filepath);
        GLuint CompileShader(GLenum type, const std::string& source);
        void CheckCompileErrors(GLuint object, const std::string& type);
        GLint GetUniformLocation(const std::string& name) const;
};