//
// Created by RFMinePC on 2/14/2021.
//

#include "Shader.h"

Shader::Shader(std::string vertPath, std::string fragPath, bool printSource)
    :m_PrintSource(printSource) {

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
    if (m_PrintSource) {
        std::cout << source << std::endl;
    }

    printf("Compiling Vertex Shader : \n");
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


    printf("Compiling Fragment Shader : \n");
    m_Frag = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_Frag, 1, &source, NULL);
    glCompileShader(m_Frag);
    if (m_PrintSource) {
        std::cout << source << std::endl;
    }

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
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform4fv(const std::string &name, int numMats, GLenum transpose, glm::mat4 mat) {
    glUniformMatrix4fv(GetUniformLocation(name), numMats, transpose, glm::value_ptr(mat));
}


void Shader::SetUniform1i(const std::string &name, int v0) {
    glUniform1i(GetUniformLocation(name), v0);
}

int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_Program, name.c_str());
    if (location == -1) {
        std::cout << "Warning: Uniform '" << name << "' doesn't exist." << std::endl;
    }

    m_UniformLocationCache[name] = location;
    return location;
}