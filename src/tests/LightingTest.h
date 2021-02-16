//
// Created by RFMinePC on 2/15/2021.
//

#ifndef OPENGLPROJECT_LIGHTINGTEST_H
#define OPENGLPROJECT_LIGHTINGTEST_H
#include "test_framework/Test.h"
#include "shader/Shader.h"
#include "camera/Camera.h"
#include "model/Vertex.h"
#include "imgui.h"
#include "handlers/InputHandler.h"

namespace test {
    class LightingTest : public Test {
    public:
        LightingTest();
        ~LightingTest();
        void OnUpdate(float dt) override;
        void OnRender() override;
        void OnResize(int width, int height) override;
        void OnImGuiRender() override;
    private:
        glm::vec3 m_LightPos = glm::vec3(2.0f, 2.0f, 2.0f);

        float objectColor[3] { 0.5f, 0.2f, 0.8f };
        float lightColor[3]  { 1.0f, 1.0f, 1.0f };

        //these are two unique objects using the 'm_VBO'
        unsigned int m_LightVAO;
        unsigned int m_CubeVAO;

        //contain data to render a cube
        unsigned int m_VBO;
        unsigned int m_IBO;

        Shader m_LightSourceShader, m_CubeShader;
        Camera m_Camera;
    };
}

#endif //OPENGLPROJECT_LIGHTINGTEST_H
