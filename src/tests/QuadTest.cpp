//
// Created by RFMinePC on 2/13/2021.
//

#include <model/Vertex.h>
#include "QuadTest.h"

test::QuadTest::QuadTest() {

    /** VERTEX SHADER **/
    const char *vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                     "}\0";

    m_VertShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_VertShader, 1, &vertexShaderSource, NULL);
    glCompileShader(m_VertShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(m_VertShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_VertShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    /** VERTEX SHADER **/


    /** FRAG SHADER **/
    const char *fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";

    m_FragShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_FragShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(m_FragShader);
    // check for shader compile errors
    glGetShaderiv(m_FragShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(m_FragShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    /** FRAG SHADER **/


    /** SHADER PROGRAM **/
    m_Program = glCreateProgram();
    glAttachShader(m_Program, m_VertShader);
    glAttachShader(m_Program, m_FragShader);
    glLinkProgram(m_Program);
    // check for linking errors
    glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(m_VertShader);
    glDeleteShader(m_FragShader);
    /** SHADER PROGRAM **/

    /** BUFFERS **/

    unsigned int indices[] = {
            0, 1, 2,
            2, 3, 0
    };

    Vertex vertices2[] = {
            {-0.5f, -0.5f, 0.0f },
            { 0.5f, -0.5f, 0.0f },
            { 0.5f,  0.5f, 0.0f },
            {-0.5f,  0.5f, 0.0f }
    };


    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_IBO);
    glBindVertexArray(m_VAO);


    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);
    /** BUFFERS **/
}

test::QuadTest::~QuadTest() {
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteProgram(m_Program);
}

void test::QuadTest::OnUpdate(float dt) {

}

void test::QuadTest::OnRender() {
    glUseProgram(m_Program);
    glBindVertexArray(m_VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}

void test::QuadTest::OnResize(int width, int height) {

}

void test::QuadTest::OnImGuiRender() {

}
