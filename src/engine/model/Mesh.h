//
// Created by RFMinePC on 2/21/2021.
//

#ifndef OPENGLPROJECT_MESH_H
#define OPENGLPROJECT_MESH_H

#include <vector>
#include "Vertex.h"
#include "engine/shader/Shader.h"
#include "engine/texture/Texture.h"

class Mesh {
public:
    Mesh();
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    ~Mesh();
    void Draw(Shader &shader, bool wireframe);
    void SetupMesh();

    // mesh data
    std::string               name;
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;
private:
    //  render data
    unsigned int VAO, VBO, IBO;

};


#endif //OPENGLPROJECT_MESH_H
