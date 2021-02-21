//
// Created by RFMinePC on 2/17/2021.
//

#ifndef OPENGLPROJECT_LIGHT_H
#define OPENGLPROJECT_LIGHT_H

struct Light {
    float type = 0.f;

    glm::vec3 position = glm::vec3(0.f);
    glm::vec3 direction = glm::vec3(0, 0, -1);;
    float cutOff;
    float outerCutOff;

    float lightIntensity;

    glm::vec3 ambient = glm::vec3(1.f);
    glm::vec3 diffuse = glm::vec3(1.f);
    glm::vec3 specular = glm::vec3(1.f);

    //attenuation (light fading)
    //atten = 1.0 / constant + linear * distance + quadratic * distance * distance
    float constant = 1.0f;
    float linear = 1.0f;
    float qaudratic = 1.0f;

    void SetDirectional(glm::vec3 _direction) {
        type = 0.f;
        direction = _direction;
    }
    void SetPoint(glm::vec3 _position) {
        type = 1.f;
        position = _position;
    }
    void SetSpotlight(glm::vec3 _position, glm::vec3 _direction, float _cutOff, float _outerCutOff) {
        type = 2.f;
        position = _position;
        direction = _direction;
        cutOff = _cutOff;
        outerCutOff = _outerCutOff;
    }
    void SetAttenuation(float _linear, float _quadratic) {
        linear = _linear;
        qaudratic = _quadratic;
    }
    void SetColors(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular = glm::vec3(1.0)) {
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
    }
    void SetIntensity(float _intensity) {
        lightIntensity = _intensity;
    }
};

#endif //OPENGLPROJECT_LIGHT_H
