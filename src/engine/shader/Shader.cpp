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

    printf("Compiling Vertex Shader : ");
    glGetShaderiv(m_Vert, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_Vert, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    } else
    {
        printf("SUCCESS - %s\n", filePath.c_str());
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


    printf("Compiling Fragment Shader : ");
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
    } else
    {
        printf("SUCCESS - %s\n", filePath.c_str());
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

    std::cout << "Created program ID : " << m_Program << std::endl;
}

void Shader::Use() const {
    glUseProgram(m_Program);
}


/**Set up shader uniforms**/
void Shader::SetUniform4f(const std::string &name, float v0, float v1, float v2, float v3) {
    glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniform4fv(const std::string &name, int numMats, GLenum transpose, glm::mat4 mat) {
    glUniformMatrix4fv(GetUniformLocation(name), numMats, transpose, glm::value_ptr(mat));
}

void Shader::SetUniform3f(const std::string &name, float v0, float v1, float v2) {
    glUniform3f(GetUniformLocation(name), v0, v1, v2);
}

void Shader::SetUniform1f(const std::string &name, float v0) {
    glUniform1f(GetUniformLocation(name), v0);
}

void Shader::SetUniform1ui(const std::string &name, unsigned int v0) {
    glUniform1ui(GetUniformLocation(name), v0);
}

void Shader::SetUniform1i(const std::string &name, int v0) {
    glUniform1i(GetUniformLocation(name), v0);
}

void Shader::SetMaterial(const std::string &name, Material mat) {
    SetUniform1i(name + ".diffuse", mat.diffuseTexture);
    SetUniform1i(name + ".specular", mat.specularTexture);
    SetUniform1f(name + ".shininess", mat.shininess);
}

void Shader::SetPointLight(const std::string &name, PointLight light) {
    SetUniform3f(name + ".position", light.pos.x, light.pos.y, light.pos.z);
    SetUniform1f(name + ".constant", light.constant);
    SetUniform1f(name + ".linear", light.linear);
    SetUniform1f(name + ".quadratic", light.quadratic);
    SetUniform3f(name + ".ambient", light.ambient.x, light.ambient.y, light.ambient.z);
    SetUniform3f(name + ".diffuse", light.diffuse.x, light.diffuse.y, light.diffuse.z);
    SetUniform3f(name + ".specular", light.specular.x, light.specular.y, light.specular.z);
}

void Shader::SetPointLightArr(const std::string &name, std::vector<PointLight>& lights) {
    for (size_t i = 0; i < lights.size(); i++) {
        std::string id = name + "[" + std::to_string(i) + "]";
        SetPointLight(id, lights[i]);
    }
}

void Shader::SetDirectionaLight(const std::string &name, DirectionalLight *light) {
    SetUniform3f(name + ".direction", light->dir.x, light->dir.y, light->dir.z);
    SetUniform3f(name + ".ambient", light->ambient.x, light->ambient.y, light->ambient.z);
    SetUniform3f(name + ".diffuse", light->diffuse.x, light->diffuse.y, light->diffuse.z);
    SetUniform3f(name + ".specular", light->specular.x, light->specular.y, light->specular.z);
}

void Shader::SetSpotLight(const std::string &name, SpotLight *light) {
    SetUniform3f(name + ".position", light->pos.x, light->pos.y, light->pos.z);
    SetUniform3f(name + ".direction", light->dir.x, light->dir.y, light->dir.z);

    SetUniform1f(name + ".cutOff", light->cutOff);
    SetUniform1f(name + ".outerCutOff", light->outerCutoff);
    SetUniform1f(name + ".intensity", light->intensity);

    SetUniform1f(name + ".constant", light->constant);
    SetUniform1f(name + ".linear", light->linear);
    SetUniform1f(name + ".quadratic", light->quadratic);

    SetUniform3f(name + ".ambient", light->ambient.x, light->ambient.y, light->ambient.z);
    SetUniform3f(name + ".diffuse", light->diffuse.x, light->diffuse.y, light->diffuse.z);
    SetUniform3f(name + ".specular", light->specular.x, light->specular.y, light->specular.z);
}

void Shader::SetEnvironment(const std::string &name, Environment env) {
    //point lights
    SetPointLightArr(name + ".pointLights", env.pLights);

    //dir light
    SetDirectionaLight(name + ".dirLight", &env.dLights[0]);

    //spot light
    SetSpotLight(name + ".spotLight", &env.sLights[0]);
}

int Shader::GetUniformLocation(const std::string &name) {
    if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
        return m_UniformLocationCache[name];

    int location = glGetUniformLocation(m_Program, name.c_str());
    if (location == -1) {
        std::cerr << "Warning: Uniform '" << name << "' doesn't exist." << std::endl;
    }

    m_UniformLocationCache[name] = location;
    return location;
}