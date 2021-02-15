//
// Created by RFMinePC on 2/14/2021.
//

#ifndef OPENGLPROJECT_MAINTEST_H
#define OPENGLPROJECT_MAINTEST_H
#include "test_framework/Test.h"
#include "shader/Shader.h"
#include "texture/Texture.h"

namespace test {
    class MainTest : public Test {
    public:
        MainTest();
        ~MainTest();
        void OnUpdate(double dt) override;
        void OnRender() override;
        void OnResize(int width, int height) override;
        void OnImGuiRender() override;
    private:
        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_IBO;

        Shader m_Shader;
        Texture m_Texture;
    private:
        float colors[4] = {0.0, 0.3, 0.5, 1.0};
    };
}

#endif //OPENGLPROJECT_MAINTEST_H
