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
#include "handlers/InputHandler.h"
#include "shader/Material.h"
#include "shader/Light.h"

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
        glm::vec3 m_LightPos = glm::vec3(2.0f, 2.0f, 2.0f);

        float objectColor[3] { 0.5f, 0.2f, 0.8f };
        glm::vec3 lightColor = glm::vec3(1.0);

        double angle;

        //these are two unique objects using the 'm_VBO'
        unsigned int m_LightVAO;
        unsigned int m_CubeVAO_0;
        unsigned int m_CubeVAO_1;

        //contain data to render a cube
        unsigned int m_VBO;
        unsigned int m_IBO;

        Material m_CubeMat = Material();
        Light m_Light = Light();

        Shader m_LightSourceShader, m_CubeShader;
        Camera m_Camera;
    };
}

#endif //OPENGLPROJECT_MATERIALTEST_H