//
// Created by RFMinePC on 2/14/2021.
//

#include "Shader.h"

Shader::Shader(std::string vertPath, std::string fragPath) {
    CompileVertShader(vertPath);
    CompileFragShader(fragPath);
    FinalizeShader();
}

Shader::~Shader() {
    glDeleteProgram(m_Program);
}

/**Set up shader program**/
void Shader::CompileVertShader(std::string& filePath) {
    std::fstream fstream(filePath);

    std::string line;
    std::stringstream ss;

    while(getline(fstream, line)) {
        ss << line << '\n';
    }
    std::string vertSourceStr = ss.str();
    const char* source = vertSourceStr.c_str();

    m_Vert = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_Vert, 1, &source, NULL);
    glCompileShader(m_Vert);

    glGetShaderiv(m_Vert, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_Vert, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
void Shader::CompileFragShader(std::string& filePath) {
    std::fstream fstream(filePath);

    std::string line;
    std::stringstream ss;

    while(getline(fstream, line)) {
        ss << line << '\n';
    }
    std::string fragSourceStr = ss.str();
    const char* source = fragSourceStr.c_str();

    m_Frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_Frag, 1, &source, NULL);
    glCompileShader(m_Frag);

    //error check
    glGetShaderiv(m_Frag, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_Frag, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
}
void Shader::FinalizeShader() {
    m_Program = glCreateProgram();
    glAttachShader(m_Program, m_Vert);
    glAttachShader(m_Program, m_Frag);
    glLinkProgram(m_Program);
    glValidateProgram(m_Program);

    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(m_Vert);
    glDeleteShader(m_Frag);
}

void Shader::Use() {
    glUseProgram(m_Program);
}

/**Set up shader uniforms**/