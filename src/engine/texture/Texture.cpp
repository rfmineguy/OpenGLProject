//
// Created by RFMinePC on 2/14/2021.
//

#include <iostream>
#include "Texture.h"


Texture::Texture()
:m_Usage(TexUse::TEX_2D) {
    std::string filepath = "../res/textures/missing/missing_diff.png";
    CreateTexture(filepath);
    m_Path = filepath;
}

Texture::Texture(std::string filePath, TexUse usage)
: m_Usage(usage) {
    CreateTexture(filePath);
    m_Path = filePath;
}

Texture::Texture(std::string filePath, TexUse usage, TexType type)
: m_Usage(usage) {
    CreateTexture(filePath);
    m_Type = type;
    m_Path = filePath;
}

Texture::Texture(Texture const &texture)
: Texture(texture.m_Path, texture.m_Usage, texture.m_Type) {
    std::cout << "Copy constructor called" << std::endl;
}

Texture &Texture::operator = (const Texture &tex) {
    std::cout << "Assignment" << std::endl;
    m_Usage = tex.m_Usage;
    m_Path = tex.m_Path;
    m_Type = tex.m_Type;
    return *this;
}

Texture::~Texture() {
    glDeleteTextures(1, &m_Texture);
    std::cout << "Deleted texture : " << m_Path << std::endl;
}

/**
 * if 'filepath' is the path to the image itself <load a Texture2D>
 * if 'filepath' is a directory <load a Cubemap>
 * **/

void Texture::CreateTexture(std::string& filePath) {
    if (m_Usage == TexUse::TEX_2D) {
        CreateTex2D(filePath);
    }
    else if (m_Usage == TexUse::CUBEMAP) {
        std::vector<std::string> defaultFileNames = {"right.jpg", "left.jpg", "top.jpg", "bottom.jpg", "front.jpg", "back.jpg"};
        CreateCubemap(filePath, defaultFileNames);
    }
    else std::cerr << "Texture::Not a valid Usage" << std::endl;

    stbi_image_free(m_Data);
}

void Texture::Use(unsigned int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    if (m_Usage == TexUse::TEX_2D) {
        glBindTexture(GL_TEXTURE_2D, m_Texture);
    }
    else if (m_Usage == TexUse::CUBEMAP) {
        glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
    }
}

void Texture::Unuse() {
    if (m_Usage == TexUse::TEX_2D)       glBindTexture(GL_TEXTURE_2D, 0);
    else if (m_Usage == TexUse::CUBEMAP) glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}

//filepath is the exact path to the texture png file
void Texture::CreateTex2D(std::string& filePath) {
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_2D, m_Texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    stbi_set_flip_vertically_on_load(1);
    m_Data = LoadImage(filePath.c_str());
    if (!m_Data) {
        std::cerr << "Tex2D::File : '" << filePath.c_str() << "' not found." << std::endl;
        std::cerr << "Tex2D::Loading missing texture in place." << std::endl;

        if(m_Type == TexType::DIFFUSE) {
            filePath = "../res/textures/missing/missing_diff.png";
            m_Data = LoadImage(filePath.c_str());
        }
        else if(m_Type == TexType::SPECULAR) {
            filePath = "../res/textures/missing/missing_spec.png";
            m_Data = LoadImage(filePath.c_str());
        }
    }

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_Data);
    glGenerateMipmap(GL_TEXTURE_2D);
    std::cout << "Created tex id : " << m_Texture << ", type=Tex2D, path=" << filePath << std::endl;
}

//filepath represents the parent directory for the 6 image files
void Texture::CreateCubemap(std::string& filePath, std::vector<std::string> fileNames) {
    glGenTextures(1, &m_Texture);
    glBindTexture(GL_TEXTURE_CUBE_MAP, m_Texture);
    GLenum err;
    while ( ( err = glGetError() ) != GL_NO_ERROR) {
        std::cerr << err << std::endl;
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

    stbi_set_flip_vertically_on_load(0);
    std::cout << "Creating cubemap texure..." << std::endl;
    for (int i = 0; i < fileNames.size(); i++) {
        m_Data = LoadImage((filePath + fileNames[i]).c_str());
        if (!m_Data) {
            std::cerr << "File : '" << filePath << fileNames[i].c_str() << "' not found." << std::endl;
            std::cerr << "Loading missing texture in place." << std::endl;
            m_Data = LoadImage("../res/textures/missing/missing_diff.png");
        }
        std::cout << "   + Adding texture : " << fileNames[i] << " " << m_Width << " x " << m_Height << " to cubemap..." << std::endl;
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, m_Data);
    }
    std::cout << "Created tex id : " << m_Texture << ", type=Cubemap, path=" << filePath << std::endl;
}

unsigned char* Texture::LoadImage(const char *path, int channelCount) {
    unsigned char* data = stbi_load(path, &m_Width, &m_Height, &m_NrChannels, channelCount);
    return data;
}