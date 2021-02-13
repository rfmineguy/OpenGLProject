//
// Created by RFMinePC on 2/13/2021.
//

#ifndef OPENGLPROJECT_QUADTEST_H
#define OPENGLPROJECT_QUADTEST_H

#include "test_framework/Test.h"

namespace test {
    class QuadTest : public Test {
    public:
        QuadTest();
        ~QuadTest();
        void OnUpdate(double dt) override;
        void OnRender() override;
        void OnResize(int width, int height) override;
        void OnImGuiRender() override;
    private:
        unsigned int m_VAO;
        unsigned int m_VBO;
        unsigned int m_IBO;
    };
}

#endif //OPENGLPROJECT_QUADTEST_H