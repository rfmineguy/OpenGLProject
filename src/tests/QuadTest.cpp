//
// Created by RFMinePC on 2/13/2021.
//

#include "QuadTest.h"

test::QuadTest::QuadTest() {
    int success;
    char infoLog[512];
    /** VERTEX SHADER **/
    {
        const char *vertexShaderSource = "#version 450 core\n"
                                         "layout (location = 0) in vec3 aPos;\n"
                                         "void main()\n"
                                         "{\n"
                                         "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                         "}\0";
        m_VertShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(m_VertShader, 1, &vertexShaderSource, NULL);
        glCompileShader(m_VertShader);
        // check for shader compile errors
        glGetShaderiv(m_VertShader, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(m_VertShader, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        } else {
            std::cout << "INFO::SHADER::VERTEX::COMPILATION_SUCCESS\n" << std::endl;
        }
    }
    /** VERTEX SHADER **/

    /** FRAG SHADER **/
    {

        const char *fragmentShaderSource = "#version 450 core\n"
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
        } else {
            std::cout << "INFO::SHADER::FRAGMENT::COMPILATION_SUCCESS\n" << std::endl;
        }
    }
    /** FRAG SHADER **/


    /** SHADER PROGRAM **/
    {
        m_Program = glCreateProgram();
        std::cout << m_Program << std::endl;
        glAttachShader(m_Program, m_VertShader);
        glAttachShader(m_Program, m_FragShader);
        glLinkProgram(m_Program);
        glValidateProgram(m_Program);
        // check for linking errors
        glGetProgramiv(m_Program, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(m_Program, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
        } else {
            std::cout << "INFO::SHADER::PROGRAM::LINKING_SUCCESS\n" << infoLog << std::endl;
        }
        glDeleteShader(m_VertShader);
        glDeleteShader(m_FragShader);
        glUseProgram(m_Program);
    }
    /** SHADER PROGRAM **/

    /** BUFFERS **/
    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };

    unsigned int indices[] = {  // note that we start from 0!
            0, 3, 1,  // first Triangle
            1, 3, 2   // second Triangle
    };
    glGenVertexArrays(1, &m_VAO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(m_VAO);

    glGenBuffers(1, &m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

    glGenBuffers(1, &m_IBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), nullptr, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(indices), indices);


    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    //glBindBuffer(GL_ARRAY_BUFFER, 0);
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // remember: do NOT unbind the EBO while a VAO is active as the bound element buffer object IS stored in the VAO; keep the EBO bound.
    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);

    /** BUFFERS **/
}

test::QuadTest::~QuadTest() {
    printf("Destructed");
    glDeleteVertexArrays(1, &m_VAO);
    glDeleteBuffers(1, &m_VBO);
    glDeleteBuffers(1, &m_IBO);
    glDeleteProgram(m_Program);
}

void test::QuadTest::OnUpdate(double dt) {

}

void test::QuadTest::OnRender() {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(m_Program);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

void test::QuadTest::OnResize(int width, int height) {

}

void test::QuadTest::OnImGuiRender() {

}
