//
// Created by RFMinePC on 2/17/2021.
//

#ifndef OPENGLPROJECT_LIGHT_H
#define OPENGLPROJECT_LIGHT_H

struct Light {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular = glm::vec3(1.0);
};

#endif //OPENGLPROJECT_LIGHT_H
