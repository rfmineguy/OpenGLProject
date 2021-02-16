//
// Created by RFMinePC on 2/15/2021.
//

#include "LightingTest.h"

test::LightingTest::LightingTest()
        : m_Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0))
        , m_LightSourceShader("../res/shaders/6_lighting/light_source_vert.shader", "../res/shaders/6_lighting/light_source_frag.shader")
        , m_CubeShader("../res/shaders/6_lighting/cube_vert.shader", "../res/shaders/6_lighting/cube_frag.shader")
        {
    Vertex vertices[] = {
            //front
            {0.0f,  0.0f, 0.0, 0.0f, 0.0f, -1.0f},  //0
            {1.0f,  0.0f, 0.0, 0.0f, 0.0f, -1.0f},  //1
            {1.0f,  1.0f, 0.0, 0.0f, 0.0f, -1.0f},  //2
            {0.0f,  1.0f, 0.0, 0.0f, 0.0f, -1.0f},  //3

            //back
            {0.0f,  0.0f, 1.0, 0.0f, 0.0f,  1.0f},  //4
            {1.0f,  0.0f, 1.0, 0.0f, 0.0f,  1.0f},  //5
            {1.0f,  1.0f, 1.0, 0.0f, 0.0f,  1.0f},  //6
            {0.0f,  1.0f, 1.0, 0.0f, 0.0f,  1.0f},  //7

            //right
            {1.0f,  0.0f, 0.0, 1.0f, 0.0f,  0.0f},  //8
            {1.0f,  0.0f, 1.0, 1.0f, 0.0f,  0.0f},  //9
            {1.0f,  1.0f, 1.0, 1.0f, 0.0f,  0.0f},  //10
            {1.0f,  1.0f, 0.0, 1.0f, 0.0f,  0.0f},  //11

            //left
            {0.0f,  0.0f, 1.0, -1.0f, 0.0f,  0.0f},  //12
            {0.0f,  0.0f, 0.0, -1.0f, 0.0f,  0.0f},  //13
            {0.0f,  1.0f, 0.0, -1.0f, 0.0f,  0.0f},  //14
            {0.0f,  1.0f, 1.0, -1.0f, 0.0f,  0.0f},  //15

            //top
            {0.0f, 1.0f, 0.0f, 0.0f, 1.0f,  0.0f},  //16
            {1.0f, 1.0f, 0.0f, 0.0f, 1.0f,  0.0f},  //17
            {1.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f},  //18
            {0.0f, 1.0f, 1.0f, 0.0f, 1.0f,  0.0f},  //19

            //bottom
            {1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f},  //20
            {1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f},  //21
            {0.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f},  //22
            {0.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f},  //23
    };
    unsigned int indices[] {
            2, 1,  0,  0,  3, 2,    //F
            4, 5,  6,  6,  7, 4,    //BA
            10, 9, 8, 8, 11, 10,    //R
            14, 13, 12, 12, 15, 14, //L
            18, 17, 16, 16, 19, 18, //T
            22, 21, 20, 20, 23, 22  //B
    };



    glGenVertexArrays(1, &m_CubeVAO);
    glGenVertexArrays(1, &m_LightVAO);

    //setup vbo
    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    //setup ibo
    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    //cube vao
    glBindVertexArray(m_CubeVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //light vao
    glBindVertexArray(m_LightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    printf("Setup buffers");
}

test::LightingTest::~LightingTest() {
    glDeleteVertexArrays(1, &m_LightVAO);
    glDeleteVertexArrays(1, &m_CubeVAO);

    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IBO);
}

double angle = 0;
void test::LightingTest::OnUpdate(float dt) {
    //update camera
    m_Camera.Update(dt);

    //move around light source
    angle += dt * 30;
    if (angle > 360) angle = 0;
    m_LightPos.x = sin(glm::radians(angle)) * 2.0f;
    m_LightPos.z = cos(glm::radians(angle)) * 2.0f;
    m_LightPos.y = sin(glm::radians(angle)) * cos(glm::radians(angle)) * 6.0f;

    //update light source shader params (small cube)
    m_CubeShader.Use();
    m_CubeShader.SetUniform3f("lightPos", m_LightPos.x, m_LightPos.y, m_LightPos.z);
    m_CubeShader.SetUniform3f("objectColor", objectColor[0], objectColor[1], objectColor[2]);
    m_CubeShader.SetUniform3f("lightColor", lightColor[0], lightColor[1], lightColor[2]);

    glm::mat4 model = glm::mat4(1.0);
    m_CubeShader.SetUniform4fv("pv", 1, GL_FALSE, m_Camera.GetProjView());
    m_CubeShader.SetUniform4fv("model", 1, GL_FALSE, model);


    m_LightSourceShader.Use();
    model = glm::mat4(1.0f);
    model = glm::translate(model, m_LightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    m_LightSourceShader.SetUniform4fv("pv", 1, GL_FALSE, m_Camera.GetProjView());
    m_LightSourceShader.SetUniform4fv("model", 1, GL_FALSE, model);
    m_LightSourceShader.SetUniform3f("lightColor", lightColor[0], lightColor[1], lightColor[2]);
}

void test::LightingTest::OnRender() {
    //second cube still renders when obscured
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    m_LightSourceShader.Use();
    glBindVertexArray(m_LightVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_CubeShader.Use();
    glBindVertexArray(m_CubeVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void test::LightingTest::OnResize(int width, int height) {

}


void test::LightingTest::OnImGuiRender() {
    ImGui::Text("Color Sliders");
    ImGui::SliderFloat3("Light (small cube)" , lightColor , 0, 1);
    ImGui::SliderFloat3("Object (large cube)", objectColor, 0, 1);

    ImGui::Value("Mouse Enabled (SPACE)", Input.mouseEnabled);
    ImGui::Value("Keys  Enabled (SPACE)", Input.keyEnabled);
}