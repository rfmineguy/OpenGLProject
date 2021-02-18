//
// Created by RFMinePC on 2/17/2021.
//

#ifndef OPENGLPROJECT_MATERIAL_H
#define OPENGLPROJECT_MATERIAL_H

#include "glm/glm.hpp"

struct Material {
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;
};

#endif //OPENGLPROJECT_MATERIAL_H
