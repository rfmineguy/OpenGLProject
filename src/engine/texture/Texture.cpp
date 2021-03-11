//
// Created by RFMinePC on 2/14/2021.
//

#include <iostream>
#include "Texture.h"

Texture::Texture(std::string filePath) {
    CreateTexture(filePath);
    m_Path = filePath;
}

Texture::Texture(std::string filePath, std::string type) {
    CreateTexture(filePath);
    m_Type = type;
    m_Path = filePath;
}

Texture::~Texture() {

}

void Texture::Use(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, m_Texture);
}


void Texture::CreateTexture(std::string filePath) {
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(1);
    std::cout << filePath << std::endl;
    unsigned char *data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
    if (data){
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    if (!data) {
        std::cout << "Texture loading failed" << std::endl;
        data = stbi_load("../res/textures/missing/missing.png", &width, &height, &nrChannels, 0);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    stbi_image_free(data);
    std::cout << "Created tex id : " << m_Texture << std::endl;
}