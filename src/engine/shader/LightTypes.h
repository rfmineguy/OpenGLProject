#pragma once

struct PointLight {
    glm::vec3 pos = glm::vec3(0.f);

    float constant = 1.0f;
    float linear = 1.0f;
    float quadratic = 1.0f;

    glm::vec3 ambient = glm::vec3(1.f);
    glm::vec3 diffuse = glm::vec3(1.f);
    glm::vec3 specular = glm::vec3(1.f);

    float lightIntensity = 2.f;

    void SetColors(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) {
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
    }

    void SetAttenuation(float _linear, float _quad) {
        constant = 1.0f;
        linear = _linear;
        quadratic = _quad;
    }

    void SetIntensity(float _lightIntensity) {
        lightIntensity = _lightIntensity;
    }

    static PointLight Default() {
        return PointLight();
    }
};

struct DirectionalLight {
    glm::vec3 dir = glm::vec3(0.f);

    glm::vec3 ambient = glm::vec3(1.f);
    glm::vec3 diffuse = glm::vec3(1.f);
    glm::vec3 specular = glm::vec3(1.f);

    void SetColors(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) {
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
    }

    static DirectionalLight Default() {
        return DirectionalLight();
    }
};

struct SpotLight {
    glm::vec3 pos = glm::vec3(1.f);
    glm::vec3 dir = glm::vec3(1.f);

    float cutOff = glm::cos(glm::radians(12.5f));
    float outerCutoff = glm::cos(glm::radians(17.5f));
    float intensity = 1.0f;
    float constant = 1.0f, linear = 1.0f, quadratic = 1.0f;

    glm::vec3 ambient = glm::vec3(1.0);
    glm::vec3 diffuse = glm::vec3(1.0);
    glm::vec3 specular = glm::vec3(1.0);

    void SetColors(glm::vec3 _ambient, glm::vec3 _diffuse, glm::vec3 _specular) {
        ambient = _ambient;
        diffuse = _diffuse;
        specular = _specular;
    }
    void SetAttenuation(float _linear, float _quad) {
        constant = 1.0f;
        linear = _linear;
        quadratic = _quad;
    }
    void SetIntensity(float _lightIntensity) {
        intensity = _lightIntensity;
    }

    static SpotLight Default() {
        return SpotLight();
    }
};