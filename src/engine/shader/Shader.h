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

class Shader {
public:
    Shader(std::string vertPath,std::string fragPath);
    ~Shader();

    void CompileVertShader(std::string& filePath);
    void CompileFragShader(std::string& filePath);
    void FinalizeShader();
    void Use();

private:
    unsigned int m_Vert;
    unsigned int m_Frag;
    unsigned int m_Program;

    int success;
    char infoLog[512];
};


#endif //OPENGLPROJECT_SHADER_H
