//
// Created by RFMinePC on 2/14/2021.
//

#ifndef OPENGLPROJECT_TEXTURE_H
#define OPENGLPROJECT_TEXTURE_H

#include <string>
#include <vector>
#include "glad/glad.h"
#include "stb_image/stb_image.h"

class Texture {
public:
    enum class TexUse {
        TEX_2D,
        CUBEMAP
    };
    enum class TexType {
        DIFFUSE,
        SPECULAR
    };

public:
    Texture();
    Texture(std::string filePath, TexUse usage, TexType type);
    Texture(std::string filePath, TexUse usage);
    Texture(const Texture& texture);
    Texture& operator = (const Texture& tex);
    ~Texture();
    void Use(unsigned int slot = 0);
    void Unuse();
    static void UnbindAll() {
        for (int i = 0; i < 32; i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            glBindTexture(GL_TEXTURE_2D, 0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        }
    }

private:
    void CreateTexture(std::string& filePath);
    void CreateTex2D(std::string& filePath);
    void CreateCubemap(std::string& filePath, std::vector<std::string> fileNames);
    unsigned char* LoadImage(const char* path, int channelCount = 0);


private:
    TexUse m_Usage;
    TexType m_Type;

public:
    unsigned int m_Texture = 0;
    std::string m_Path;

    unsigned char* m_Data;
    int m_Width;
    int m_Height;
    int m_NrChannels;
};


#endif //OPENGLPROJECT_TEXTURE_H
