//
// Created by RFMinePC on 3/5/2021.
//

#ifndef OPENGLPROJECT_MODEL2_H
#define OPENGLPROJECT_MODEL2_H

#include <string>
#include <model/Mesh.h>
#include <glm/gtx/hash.hpp>
#include "shader/Material.h"

class Model2 {
public:
    Model2(const char* dir, const char* name);
    ~Model2();
    void LoadFile(const char* name);
    void Draw(Shader &shader, bool wireframe = false);
    void PrintData();
    std::string ReadFileContents(const char* name);

public:
    Material material;
    Texture m_Spec, m_Diff;
private:
    std::string m_Dir;
    Mesh mesh;
};


#endif //OPENGLPROJECT_MODEL2_H
