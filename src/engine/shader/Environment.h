//
// Created by RFMinePC on 3/6/2021.
//

#ifndef OPENGLPROJECT_ENVIRONMENT_H
#define OPENGLPROJECT_ENVIRONMENT_H

#include "LightTypes.h"
#include "vector"

struct Environment {
    std::vector<PointLight> pLights       = { PointLight::Default(), PointLight::Default(), PointLight::Default(), PointLight::Default() };
    std::vector<DirectionalLight> dLights = { DirectionalLight::Default() };
    std::vector<SpotLight> sLights        = { SpotLight::Default() };
};

#endif //OPENGLPROJECT_ENVIRONMENT_H
