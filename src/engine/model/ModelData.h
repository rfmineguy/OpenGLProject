//
// Created by RFMinePC on 2/14/2021.
//

#ifndef OPENGLPROJECT_MODELDATA_H
#define OPENGLPROJECT_MODELDATA_H
#include "Vertex.h"
#include <vector>

struct ModelData {
    Vertex vertices[];
    unsigned int indices[];
};


#endif //OPENGLPROJECT_MODELDATA_H
