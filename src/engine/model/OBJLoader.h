//
// Created by RFMinePC on 3/5/2021.
//

#ifndef OPENGLPROJECT_OBJLOADER_H
#define OPENGLPROJECT_OBJLOADER_H
#include "Mesh.h"
#include "shader/Material.h"
#include <fstream>

class OBJLoader {
public:
    OBJLoader();
    Mesh ParseOBJ(std::string filepath);
    Material ParseMat(std::string filepath);
    std::vector<std::string> SplitLine(std::string input, char splitby) {
        std::vector<std::string> output;

        std::stringstream ss(input);
        std::string str;
        while(std::getline(ss, str, splitby)) {
            output.push_back(str);
        }
        return output;
    };
    Mesh m_Mesh;
    Material m_Material;
};
#endif //OPENGLPROJECT_OBJLOADER_H
