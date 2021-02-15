//
// Created by RFMinePC on 2/14/2021.
//

#include "ShaderTest.h"
#include "model/Vertex.h"

#include "imgui/imgui.h"

test::ShaderTest::ShaderTest()
    :m_Shader("../res/shaders/1/vert.shader", "../res/shaders/1/frag.shader"){

    /** BUFFERS **/
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

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    /** BUFFERS **/
}

test::ShaderTest::~ShaderTest() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
}

void test::ShaderTest::OnUpdate(double dt) {

}

void test::ShaderTest::OnRender() {
    m_Shader.Use();
    m_Shader.SetUniform4f("inColor", colors[0], colors[1], colors[2], colors[3]);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void test::ShaderTest::OnResize(int width, int height) {

}

void test::ShaderTest::OnImGuiRender() {
    ImGui::SliderFloat4("inColor", colors, 0, 1);
}

