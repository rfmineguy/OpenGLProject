//
// Created by RFMinePC on 3/5/2021.
//

#ifndef OPENGLPROJECT_MODEL_H
#define OPENGLPROJECT_MODEL_H

#include <string>
#include <model/Mesh.h>
#include <glm/gtx/hash.hpp>
#include "shader/Material.h"
#include <memory>

class Model {
public:
    enum class ModelUsage {
        NORMAL,
        SKYBOX
    };
public:
    Model(const char* dir, const char* name, ModelUsage usage, bool printdata = false, bool invertNormals = false);
    ~Model();
    void LoadFile(const char* name);
    void Draw(Shader &shader, bool wireframe = false);
    void PrintData();
    std::string ReadFileContents(const char* name);

public:
    Material material;
    std::unique_ptr<Texture> m_Spec, m_Diff;
    ModelUsage m_Usage;

private:
    bool m_InvertNormals;
    std::string m_ModelName;
    std::string m_Dir;
    Mesh mesh;
};


#endif //OPENGLPROJECT_MODEL_H
