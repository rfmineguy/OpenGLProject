//
// Created by RFMinePC on 2/17/2021.
//

#ifndef OPENGLPROJECT_MATERIAL_H
#define OPENGLPROJECT_MATERIAL_H

#include "glm/glm.hpp"

struct Material {
    unsigned int diffuseTexture = 0;
    unsigned int specularTexture = 1;
    float shininess;
};

#endif //OPENGLPROJECT_MATERIAL_H
