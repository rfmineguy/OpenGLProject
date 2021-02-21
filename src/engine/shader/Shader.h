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
#include <vector>
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader/Material.h"
#include "shader/LightTypes.h"

class Shader {
public:
    Shader(std::string vertPath,std::string fragPath, bool printSource = false);
    ~Shader();

    void Use();
    void SetUniform1ui(const std::string& name, unsigned int v0);
    void SetUniform1i(const std::string& name, int v0);
    void SetUniform1f(const std::string& name, float v0);
    void SetUniform3f(const std::string& name, float v0, float v1, float v2);
    void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void SetUniform4fv(const std::string& name, int numMats, GLenum transpose, glm::mat4 mat);
    void SetMaterial(const std::string& name, Material mat);
    void SetPointLight(const std::string& name, PointLight light);
    void SetPointLightArr(const std::string& name, std::vector<PointLight>& lights);

    void SetDirectionaLight(const std::string& name, DirectionalLight* light);
    void SetSpotLight(const std::string& name, SpotLight* light);
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
