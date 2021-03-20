//
// Created by RFMinePC on 3/5/2021.
//

#include "Model.h"
#include "tiny_obj_loader/tiny_obj_loader.h"

//the diffuse texture should be named "<obj filename>_diff.png"
Model::Model(const char* dir, const char* name, ModelUsage usage, bool printdata, bool invertNormals)
: m_Dir(dir),
m_Usage(usage),
m_InvertNormals(invertNormals) {
    if (usage == ModelUsage::NORMAL) {
        m_Spec = std::make_unique<Texture>(m_Dir + name + "_spec.png", Texture::TexUse::TEX_2D, Texture::TexType::SPECULAR);
        m_Diff = std::make_unique<Texture>(m_Dir + name + "_diff.png", Texture::TexUse::TEX_2D, Texture::TexType::DIFFUSE);
    } else if (usage == Model::ModelUsage::SKYBOX) {
        // no spec for skybox
        m_Diff = std::make_unique<Texture>("../res/textures/skybox/", Texture::TexUse::CUBEMAP);
    }
    LoadFile(name);
    if (printdata)
        PrintData();

    m_ModelName = name;
    std::cout << m_ModelName << std::endl << std::endl;
}

Model::~Model() {

}

void Model::LoadFile(const char* name) {
    std::string contents = ReadFileContents(name);

    std::istringstream sourceStream(contents);
    //std::cout << contents << std::endl;

    tinyobj::attrib_t attributes;
    std::vector<tinyobj::shape_t> shapes;
    std::vector<tinyobj::material_t> materials;
    std::string warning;
    std::string error;

    if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &error, &sourceStream) )
    {
        throw std::runtime_error("ast::assets::loadOBJFile: Error: " + warning + error);
    }

    std::vector<Vertex> Vertices;
    std::vector<uint32_t> Indices;
    std::unordered_map<glm::vec3, uint32_t> uniqueVertices = std::unordered_map<glm::vec3, uint32_t>();

    for (const auto& shape : shapes) {
        for (const auto& index : shape.mesh.indices) {
            int vertInd = index.vertex_index;
            int normInd = index.normal_index;
            int texInd = index.texcoord_index;
            float normalDir = m_InvertNormals ? -1 : 1;
            glm::vec3 position{
                    attributes.vertices[3 * vertInd + 0],
                    attributes.vertices[3 * vertInd + 1],
                    attributes.vertices[3 * vertInd + 2]};
            glm::vec3 normal{
                    attributes.normals[3 * normInd + 0] * normalDir,
                    attributes.normals[3 * normInd + 1] * normalDir,
                    attributes.normals[3 * normInd + 2] * normalDir,
            };
            glm::vec2 texCoord{
                    attributes.texcoords[2 * texInd + 0],
                    attributes.texcoords[2 * texInd + 1]
            };
            Vertex v = {
                    {position.x, position.y, position.z},
                    {normal.x, normal.y, normal.z},
                    {texCoord.x, texCoord.y}
            };

            //if (uniqueVertices.count(position) == 0) {
                uniqueVertices[position] = static_cast<uint32_t>(Vertices.size());
                Vertices.push_back(v);
            //}
            Indices.push_back(uniqueVertices[position]);
        }
    }
    for (const auto& mat : materials) {
        //future support for material files to modify imported objects
    }
    mesh.modelName = m_ModelName + "_mesh";
    mesh.vertices = Vertices;
    mesh.indices = Indices;
    mesh.SetupMesh();

    material.diffuseTexture = 0;
    material.specularTexture = 1;
    material.shininess = 32.f;
}

std::string Model::ReadFileContents(const char* name) {
    std::fstream fstream;
    fstream.open(m_Dir + name + ".obj");
    std::string currentLine;
    std::stringstream fileContents;
    while(std::getline(fstream, currentLine)) {
        fileContents << currentLine << "\n";
    }
    if (fileContents.str().length() <= 0) {
        std::cerr << "Failed to read : " << m_Dir << name << ".obj" << std::endl;
        return NULL;
    }
    return fileContents.str();
}

void Model::PrintData() {
    printf("Mesh Vertices : %d\n", mesh.vertices.size());
    for(int i = 0; i < mesh.vertices.size(); i++) {
        printf("    - Vertex %d { \n", i);
        printf("      + Position { %0.4f %0.4f %0.4f }\n", mesh.vertices[i].Pos[0], mesh.vertices[i].Pos[1], mesh.vertices[i].Pos[2]);
        printf("      + Normal { %0.4f %0.4f %0.4f }\n", mesh.vertices[i].Normal[0], mesh.vertices[i].Normal[1], mesh.vertices[i].Normal[2]);
        printf("      + TexCoords { %0.4f %0.4f }\n", mesh.vertices[i].TexCoords[0], mesh.vertices[i].TexCoords[1]);
    }
    printf("Mesh Indices : %d\n", mesh.indices.size());
    for(int i = 0; i < mesh.indices.size(); i+=6) {
        printf("  - %d %d %d %d %d %d \n", mesh.indices[i], mesh.indices[i+1]
                                             , mesh.indices[i+2], mesh.indices[i+3]
                                             , mesh.indices[i+4], mesh.indices[i+5]);
    }
}

void Model::Draw(Shader &shader, bool wireframe) {
    //possibly wasteful, but it works
    if (m_InvertNormals) {
        glFrontFace(GL_CW);
    } else {
        glFrontFace(GL_CCW);
    }
    shader.Use();
    if (m_Usage == ModelUsage::NORMAL) {
        m_Spec->Use(0);
        m_Diff->Use(1);
    }
    if (m_Usage == ModelUsage::SKYBOX) {
        m_Diff->Use(2);
    }
    mesh.Draw(shader, wireframe);
}