//
// Created by RFMinePC on 2/14/2021.
//

#ifndef OPENGLPROJECT_SHADER_H
#define OPENGLPROJECT_SHADER_H

#include "glad/glad.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <unordered_map>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"

class Shader {
public:
    Shader(std::string vertPath,std::string fragPath, bool printSource = false);
    ~Shader();

    void Use();
    void SetUniform1i(const std::string& name, int v0);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform4fv(const std::string& name, int numMats, GLenum transpose, glm::mat4 mat);
private:
    void CompileVertShader(std::string& filePath);
    void CompileFragShader(std::string& filePath);
    void FinalizeShader();
    int GetUniformLocation(const std::string& location);

private:
    std::unordered_map<std::string, int> m_UniformLocationCache;
    bool m_PrintSource;

private:
    unsigned int m_Vert;
    unsigned int m_Frag;
    unsigned int m_Program;

    int success;
    char infoLog[512];

    std::string shaderPath;
};


#endif //OPENGLPROJECT_SHADER_H
