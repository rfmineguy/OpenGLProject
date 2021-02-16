//
// Created by RFMinePC on 2/15/2021.
//

#ifndef OPENGLPROJECT_TEXTUREDCUBETEST_H
#define OPENGLPROJECT_TEXTUREDCUBETEST_H


#include "test_framework/Test.h"
#include "shader/Shader.h"
#include "texture/Texture.h"
#include "camera/Camera.h"

#include "model/Vertex.h"
#include "imgui.h"

namespace test{
    class TexturedCubeTest : public Test {
    public:
        TexturedCubeTest();
        ~TexturedCubeTest();
        void OnUpdate(float dt) override;
        void OnRender() override;
        void OnResize(int width, int height) override;
        void OnImGuiRender() override;
    private:
        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_IBO;

        Shader m_Shader;
        Texture m_Texture;
        Camera m_Camera;
    };
}


#endif //OPENGLPROJECT_TEXTUREDCUBETEST_H
