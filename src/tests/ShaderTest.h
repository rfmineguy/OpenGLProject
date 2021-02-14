//
// Created by RFMinePC on 2/14/2021.
//

#ifndef OPENGLPROJECT_SHADERTEST_H
#define OPENGLPROJECT_SHADERTEST_H
#include "test_framework/Test.h"
#include "shader/Shader.h"

namespace test {
    class ShaderTest : public Test {
    public:
        ShaderTest();
        ~ShaderTest();
        void OnUpdate(double dt) override;
        void OnRender() override;
        void OnResize(int width, int height) override;
        void OnImGuiRender() override;
    private:
        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_IBO;

        Shader m_Shader;
    };
}

#endif //OPENGLPROJECT_SHADERTEST_H
