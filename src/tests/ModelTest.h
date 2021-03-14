//
// Created by RFMinePC on 2/21/2021.
//

#ifndef OPENGLPROJECT_MODELTEST_H
#define OPENGLPROJECT_MODELTEST_H

#include "test_framework/Test.h"
#include "model/Model.h"
#include "shader/Shader.h"
#include "shader/Environment.h"
#include "camera/Camera.h"

namespace test{
    class ModelTest : public Test {
    public:
        ModelTest();
        ~ModelTest();
        void OnUpdate(float dt) override;
        void OnRender() override;
        void OnResize(int width, int height) override;
        void OnImGuiRender() override;

    public:
        Environment environment;
    private:
        Model m_Model, m_SkyboxModel;
        Shader m_Shader, m_SkyboxShader;
        Camera m_Camera;

    private:
        bool m_IsWireframe = false;
    };
}


#endif //OPENGLPROJECT_MODELTEST_H
