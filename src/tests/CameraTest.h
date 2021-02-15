//
// Created by RFMinePC on 2/15/2021.
//

#ifndef OPENGLPROJECT_CAMERATEST_H
#define OPENGLPROJECT_CAMERATEST_H
#include "test_framework/Test.h"

#include "shader/Shader.h"
#include "camera/Camera.h"

namespace test {
    class CameraTest : public Test {
    public:
        CameraTest();
        ~CameraTest() override;
        void OnUpdate(float dt) override;
        void OnRender() override;
        void OnResize(int width, int height) override;
        void OnImGuiRender() override;
    private:
        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_IBO;

        Shader m_Shader;
        Camera m_Camera;
    };
}


#endif //OPENGLPROJECT_CAMERATEST_H
