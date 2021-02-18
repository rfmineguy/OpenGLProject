//
// Created by RFMinePC on 2/16/2021.
//

#include "MaterialTest.h"

test::MaterialTest::MaterialTest()
        : m_Camera(glm::vec3(0, 0, 3), glm::vec3(0, 0, 0))
        , m_LightSourceShader("../res/shaders/7_materialLighting/light_source_vert.shader", "../res/shaders/7_materialLighting/light_source_frag.shader")
        , m_CubeShader("../res/shaders/7_materialLighting/cube_vert.shader", "../res/shaders/7_materialLighting/cube_frag.shader")
{
    Vertex vertices[] = {
            //front
            {{0.0f,  0.0f, 0.0}, {0.0f, 0.0f, -1.0f}, {}},  //0
            {{1.0f,  0.0f, 0.0}, {0.0f, 0.0f, -1.0f}, {}},  //1
            {{1.0f,  1.0f, 0.0}, {0.0f, 0.0f, -1.0f}, {}},  //2
            {{0.0f,  1.0f, 0.0}, {0.0f, 0.0f, -1.0f}, {}},  //3

            //back
            {{0.0f,  0.0f, 1.0}, {0.0f, 0.0f,  1.0f}, {}}, //4
            {{1.0f,  0.0f, 1.0}, {0.0f, 0.0f,  1.0f}, {}}, //5
            {{1.0f,  1.0f, 1.0}, {0.0f, 0.0f,  1.0f}, {}}, //6
            {{0.0f,  1.0f, 1.0}, {0.0f, 0.0f,  1.0f}, {}}, //7

            //right
            {{1.0f,  0.0f, 0.0}, {1.0f, 0.0f,  0.0f}, {}}, //8
            {{1.0f,  0.0f, 1.0}, {1.0f, 0.0f,  0.0f}, {}}, //9
            {{1.0f,  1.0f, 1.0}, {1.0f, 0.0f,  0.0f}, {}}, //10
            {{1.0f,  1.0f, 0.0}, {1.0f, 0.0f,  0.0f}, {}}, //11

            //left
            {{0.0f,  0.0f, 1.0}, {-1.0f, 0.0f,  0.0f}, {}}, //12
            {{0.0f,  0.0f, 0.0}, {-1.0f, 0.0f,  0.0f}, {}}, //13
            {{0.0f,  1.0f, 0.0}, {-1.0f, 0.0f,  0.0f}, {}}, //14
            {{0.0f,  1.0f, 1.0}, {-1.0f, 0.0f,  0.0f}, {}}, //15

            //top
            {{0.0f, 1.0f, 0.0f}, {0.0f, 1.0f,  0.0f}, {}}, //16
            {{1.0f, 1.0f, 0.0f}, {0.0f, 1.0f,  0.0f}, {}}, //17
            {{1.0f, 1.0f, 1.0f}, {0.0f, 1.0f,  0.0f}, {}}, //18
            {{0.0f, 1.0f, 1.0f}, {0.0f, 1.0f,  0.0f}, {}}, //19

            //bottom
            {{1.0f, 0.0f, 1.0f}, {0.0f, -1.0f,  0.0f}, {}}, //20
            {{1.0f, 0.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {}}, //21
            {{0.0f, 0.0f, 0.0f}, {0.0f, -1.0f,  0.0f}, {}}, //22
            {{0.0f, 0.0f, 1.0f}, {0.0f, -1.0f,  0.0f}, {}}, //23
    };
    unsigned int indices[] {
            2, 1,  0,  0,  3, 2,    //F
            4, 5,  6,  6,  7, 4,    //BA
            10, 9, 8, 8, 11, 10,    //R
            14, 13, 12, 12, 15, 14, //L
            18, 17, 16, 16, 19, 18, //T
            22, 21, 20, 20, 23, 22  //B
    };

    glGenVertexArrays(1, &m_CubeVAO_0);
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
    glBindVertexArray(m_CubeVAO_0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Pos));
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    glEnableVertexAttribArray(1);

    //light vao
    glBindVertexArray(m_LightVAO);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Pos));
    glEnableVertexAttribArray(0);

    printf("Setup buffers");
}

test::MaterialTest::~MaterialTest() {
    glDeleteVertexArrays(1, &m_LightVAO);
    glDeleteVertexArrays(1, &m_CubeVAO_0);

    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IBO);
}

float time = 0;
void test::MaterialTest::OnUpdate(float dt) {
    m_Camera.Update(dt);

    /** START VALUE CALCULATIONS **/
    time += dt;
    angle += dt * 30;
    if (angle > 360) angle = 0;
    m_LightPos.x = sin(glm::radians(angle)) * 2.0f;
    m_LightPos.z = cos(glm::radians(angle)) * 2.0f;
    m_LightPos.y = sin(glm::radians(angle)) * cos(glm::radians(angle)) * 6.0f;

    lightColor.x = abs(sin(time * 2.0f));
    lightColor.y = abs(sin(time * 0.7f));
    lightColor.z = abs(sin(time * 1.3f));
    glm::vec3 diffuseColor = lightColor   * glm::vec3(0.5f); // decrease the influence
    glm::vec3 ambientColor = diffuseColor * glm::vec3(0.6f); // low influence
    /** END VALUE CALCULATIONS **/

    /**START MATERIAL UPDATES**/
    m_Light.position = m_LightPos;
    m_Light.diffuse = diffuseColor;
    m_Light.ambient = ambientColor;

    m_CubeMat.ambient = glm::vec3(1.0f, 0.5f, 0.31f);
    m_CubeMat.diffuse = glm::vec3(1.0f, 0.5f, 0.31f);
    m_CubeMat.specular = glm::vec3(0.5f, 0.5f, 0.5f);
    m_CubeMat.shininess = 32.f;
    /**END MATERIAL UPDATES**/

    /**START SHADER 'MODIFICATION'**/
    m_CubeShader.Use();
    m_CubeShader.SetLight("light", m_Light);
    m_CubeShader.SetMaterial("material", m_CubeMat);
    m_CubeShader.SetUniform3f("viewPos", m_Camera.m_CamPos.x, m_Camera.m_CamPos.y, m_Camera.m_CamPos.z);

    m_CubeShader.SetUniform4fv("pv", 1, GL_FALSE, m_Camera.GetProjView());
    glm::mat4 model = glm::mat4(1.0f);
    m_CubeShader.SetUniform4fv("model", 1, GL_FALSE, model);

    //setup the light source's uniforms
    m_LightSourceShader.Use();
    m_LightSourceShader.SetUniform4fv("pv", 1, GL_FALSE, m_Camera.GetProjView());
    model = glm::mat4(1.0f);
    model = glm::translate(model, m_LightPos);
    model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
    m_LightSourceShader.SetUniform4fv("model", 1, GL_FALSE, model);
    m_LightSourceShader.SetUniform3f("lightColor", lightColor.x, lightColor.y, lightColor.z);
    /**END SHADER 'MODIFICATION'**/
}

void test::MaterialTest::OnRender() {
    //second cube still renders when obscured
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );

    m_LightSourceShader.Use();
    glBindVertexArray(m_LightVAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

    m_CubeShader.Use();
    glBindVertexArray(m_CubeVAO_0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}

void test::MaterialTest::OnResize(int width, int height) {
    Test::OnResize(width, height);
}

void test::MaterialTest::OnImGuiRender() {
    Test::OnImGuiRender();
    ImGui::Text("%0.4f %0.4f %0.4f", lightColor.x, lightColor.y, lightColor.z);
    ImGui::Text("%0.4f %0.4f %0.4f", m_LightPos.x, m_LightPos.y, m_LightPos.z);
}