//
// Created by RFMinePC on 2/17/2021.
//

#ifndef OPENGLPROJECT_MATERIAL_H
#define OPENGLPROJECT_MATERIAL_H

#include "glm/glm.hpp"

struct Material {
    int diffuseTexture = 0;
    int specularTexture = 1;
    float shininess = 32.0f;
};

#endif //OPENGLPROJECT_MATERIAL_H
