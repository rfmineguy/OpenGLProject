//
// Created by RFMinePC on 2/15/2021.
//

#include "CameraTest.h"
#include "model/Vertex.h"

test::CameraTest::CameraTest()
: m_Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0))
, m_Shader("../res/shaders/4_camera/vert.shader", "../res/shaders/4_camera/frag.shader", true)
{
    Vertex vertices[] = {
            {-0.5f, -0.5f, 0.0f },
            { 0.5f, -0.5f, 0.0f },
            { 0.5f,  0.5f, 0.0f },
            {-0.5f,  0.5f, 0.0f }
    };

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)(0 * sizeof(float)));
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    /** BUFFERS **/
}

test::CameraTest::~CameraTest() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IBO);
}

void test::CameraTest::OnUpdate(float dt) {
    m_Camera.Update(dt);
    m_Shader.Use();
    m_Shader.SetUniform4fv("mvp", 1, GL_FALSE, m_Camera.GetProjView());
}

void test::CameraTest::OnRender() {
    m_Shader.Use();

    glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void test::CameraTest::OnResize(int width, int height) {
    Test::OnResize(width, height);
}

void test::CameraTest::OnImGuiRender() {
    Test::OnImGuiRender();
}
