//
// Created by RFMinePC on 2/15/2021.
//

#include "CubeTest.h"

test::CubeTest::CubeTest()
:m_Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0))
,m_Shader("../res/shaders/4_camera/vert.shader", "../res/shaders/4_camera/frag.shader")
{
    //cube
    Vertex vertices[] = {
            //front
            {0.0f,  0.0f, 0.0f,  0.0f, 0.0f},  //0
            {1.0f,  0.0f, 0.0f,  1.0f, 0.0f},  //1
            {1.0f,  1.0f, 0.0f,  1.0f, 1.0f},  //2
            {0.0f,  1.0f, 0.0f,  0.0f, 1.0f},  //3

            //back
            {0.0f,  0.0f, 1.0f,  0.0f, 0.0f},  //4
            {1.0f,  0.0f, 1.0f,  1.0f, 0.0f},  //5
            {1.0f,  1.0f, 1.0f,  1.0f, 1.0f},  //6
            {0.0f,  1.0f, 1.0f,  0.0f, 1.0f},  //7

            //right
            {1.0f,  0.0f, 0.0f,  0.0f, 0.0f},  //8
            {1.0f,  0.0f, 1.0f,  1.0f, 0.0f},  //9
            {1.0f,  1.0f, 1.0f,  1.0f, 1.0f},  //10
            {1.0f,  1.0f, 0.0f,  0.0f, 1.0f},  //11

            //left
            {0.0f,  0.0f, 1.0f,  0.0f, 0.0f},  //12
            {0.0f,  0.0f, 0.0f,  1.0f, 0.0f},  //13
            {0.0f,  1.0f, 0.0f,  1.0f, 1.0f},  //14
            {0.0f,  1.0f, 1.0f,  0.0f, 1.0f},  //15

            //top
            {0.0f, 1.0f, 0.0f,   0.0f, 0.0f},  //16
            {1.0f, 1.0f, 0.0f,   1.0f, 0.0f},  //17
            {1.0f, 1.0f, 1.0f,   1.0f, 1.0f},  //18
            {0.0f, 1.0f, 1.0f,   0.0f, 1.0f},  //19

            //bottom
            {1.0f, 0.0f, 1.0f,   1.0f, 1.0f}, //20
            {1.0f, 0.0f, 0.0f,   1.0f, 0.0f}, //21
            {0.0f, 0.0f, 0.0f,   0.0f, 0.0f}, //22
            {0.0f, 0.0f, 1.0f,   0.0f, 1.0f}, //23
    };
    unsigned int indices[] {
        2, 1,  0,  0,  3, 2,    //F
        4, 5,  6,  6,  7, 4,    //BA
        10, 9, 8, 8, 11, 10,    //R
        14, 13, 12, 12, 15, 14, //L
        18, 17, 16, 16, 19, 18, //T
        22, 21, 20, 20, 23, 22  //B
    };

    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
}

test::CubeTest::~CubeTest() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IBO);
}

void test::CubeTest::OnUpdate(float dt) {
    m_Camera.Update(dt);
    m_Shader.Use();
    m_Shader.SetUniform4fv("mvp", 1, GL_FALSE, m_Camera.GetProjView());
}

void test::CubeTest::OnRender() {
    m_Shader.Use();

    glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void test::CubeTest::OnResize(int width, int height) {
    Test::OnResize(width, height);
}

void test::CubeTest::OnImGuiRender() {
    Test::OnImGuiRender();

    ImGui::Text("CamPos -> %0.04f %0.04f %0.04f", m_Camera.m_CamPos.x, m_Camera.m_CamPos.y, m_Camera.m_CamPos.z);
    ImGui::Text("CamFront -> %0.04f %0.04f %0.04f", m_Camera.m_CameraFront.x, m_Camera.m_CameraFront.y, m_Camera.m_CameraFront.z);
}
