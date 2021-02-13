//
// Created by RFMinePC on 2/13/2021.
//

#include "QuadTest.h"

test::QuadTest::QuadTest() {
    float vertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f,  0.5f, 0.0f
    };
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

test::QuadTest::~QuadTest() {

}

void test::QuadTest::OnUpdate(double dt) {

}

void test::QuadTest::OnRender() {

}

void test::QuadTest::OnResize(int width, int height) {

}

void test::QuadTest::OnImGuiRender() {

}
