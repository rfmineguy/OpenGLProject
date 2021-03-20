//
// Created by RFMinePC on 2/21/2021.
//

#include "Mesh.h"


Mesh::Mesh() {

}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) {
    this->vertices = vertices;
    this->indices = indices;

    SetupMesh();
}

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures) {
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    SetupMesh();
}

Mesh::~Mesh() {
    std::cout << "Mesh Destructor" << std::endl;
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &IBO);
    this->vertices.clear();
    this->indices.clear();
    this->textures.clear();
}

void Mesh::SetupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &IBO);

    glBindVertexArray(VAO);

    //vbo
    std::cout << vertices.size() * sizeof(float) << std::endl;
    //position

    //8 * (32 / 4) = 64
    //convert vector to normal float[]
    Vertex arr[vertices.size() * (sizeof(Vertex) / sizeof(float))];
    std::copy(vertices.begin(), vertices.end(), arr);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(arr), arr, GL_STATIC_DRAW);


    std::cout << modelName <<  " -> Indices count : " << indices.size() << std::endl;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Pos));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
    // vertex texture coords
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
}

void Mesh::Draw(Shader &shader, bool wireframe) {
    if (wireframe) {
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    } else {
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    }
    glBindVertexArray(VAO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IBO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}