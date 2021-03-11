//
// Created by RFMinePC on 3/5/2021.
//
#include "OBJLoader.h"

OBJLoader::OBJLoader() {

}

Mesh OBJLoader::ParseOBJ(std::string filepath) {
    std::cout << "ParseOBJ" << std::endl;
    std::fstream stream;
    stream.open(filepath);

    std::string line;
    Mesh mesh;

    //stores data for 'f' check
    std::vector<Vertex> Vertices;
    std::vector<unsigned int> Indices;
    std::vector<glm::vec3> Positions = std::vector<glm::vec3>();
    std::vector<glm::vec2> TexCoords = std::vector<glm::vec2>();;
    std::vector<glm::vec3> Normals = std::vector<glm::vec3>();

    int currentFace = 0;
    while (std::getline(stream, line)) {
        std::vector<std::string> tokens = SplitLine(line, ' ');
        if (tokens[0] == "o") {
            mesh.name = tokens[1];
        }
        if (tokens[0] == "v") {
            glm::vec3 pos = glm::vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            printf("Vertex : { %0.4f, %0.4f, %0.4f }\n", pos.x, pos.y, pos.z);
            Positions.push_back(pos);
        }
        if (tokens[0] == "vt") {
            glm::vec2 texCoord = glm::vec2(std::stof(tokens[1]), std::stof(tokens[2]));
            printf("Texture Coord : { %0.4f, %0.4f }\n", texCoord.x, texCoord.y);
            TexCoords.push_back(texCoord);
        }
        if (tokens[0] == "vn") {
            glm::vec3 vertexNormal = glm::vec3(std::stof(tokens[1]), std::stof(tokens[2]), std::stof(tokens[3]));
            printf("Vertex Normal : { %0.4f, %0.4f, %0.4f }\n", vertexNormal.x, vertexNormal.y, vertexNormal.z);
            Normals.push_back(vertexNormal);
        }

        //this connects all the data collected above into individual vertices (Vertex.h)
        //requires that the above are put in arrays in order to how they were found

        if (tokens[0] == "f") {
            printf("Found 'f' line, connecting vertex data together...\n");
            //format -> f v1/vt1/vn1 v2/vt2/vn2 v3/vt3/vn3 v4/vt4/vn4
            for (int i = 1; i < tokens.size(); i++) {
                std::vector<std::string> vStr = SplitLine(tokens[i], '/');

                printf("Vertex : { v_id - %s, tex_id - %s, norm_id - %s\n",
                       vStr[0].c_str(),
                       vStr[1].c_str(),
                       vStr[2].c_str());

                //there are only six normals, one per face of 4 vertices
                Vertex vertex = {
                        {Positions[std::stoi(vStr[0])].x, Positions[std::stoi(vStr[0])].y, Positions[std::stoi(vStr[0])].z},
                        {Normals[currentFace].x, Normals[currentFace].y, Normals[currentFace].z  },
                        {TexCoords[std::stoi(vStr[2])].x, TexCoords[std::stoi(vStr[2])].y}
                };
                Vertices.push_back(vertex);

                /*indices need special work
                    - parse the indices in a custom way to support the data format I use
                 */

                Indices.push_back(std::stoi(vStr[0]));
            }
            currentFace++;
        }
    }
    return Mesh(Vertices, Indices);
}

Material OBJLoader::ParseMat(std::string filepath) {
    return Material();
}
