//
// Created by RFMinePC on 2/16/2021.
//

#ifndef OPENGLPROJECT_MATERIALTEST_H
#define OPENGLPROJECT_MATERIALTEST_H
#include "test_framework/Test.h"
#include "shader/Shader.h"
#include "camera/Camera.h"
#include "model/Vertex.h"
#include "imgui.h"
#include <vector>

#include "handlers/InputHandler.h"
#include "shader/Material.h"
#include "shader/LightTypes.h"
#include "texture/Texture.h"
#include <random>

namespace test{
    class MaterialTest : public Test {
    public:
        MaterialTest();
        ~MaterialTest();
        void OnUpdate(float dt) override;
        void OnRender() override;
        void OnResize(int width, int height) override;
        void OnImGuiRender() override;
    private:
        const unsigned int POINT_LIGHT_COUNT = 4;
        glm::vec3 m_LightPos = glm::vec3(3.5f, 3.5f, 3.5f);

        glm::vec3 m_lightColor = glm::vec3(1.0);
        glm::vec3 m_RotationAxis = glm::vec3(1.0);

        double angle = 0;

        //these are two unique objects using the 'm_VBO'
        unsigned int m_LightVAO;
        unsigned int m_CubeVAO_0;
        unsigned int m_CubeVAO_1;

        //contain data to render a cube
        unsigned int m_VBO;
        unsigned int m_IBO;

        Material m_CubeMat = Material();
        std::vector<PointLight> m_PointLights = std::vector<PointLight>(POINT_LIGHT_COUNT);
        std::vector<glm::vec3> m_PointLightColors = std::vector<glm::vec3>(POINT_LIGHT_COUNT);
        DirectionalLight m_DirLight;
        SpotLight m_SpotLight;


        Shader m_LightSourceShader, m_CubeShader;
        Camera m_Camera;

        Texture m_DiffuseTex, m_SpecularTex;
    };
}

#endif //OPENGLPROJECT_MATERIALTEST_H