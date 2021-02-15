//
// Created by RFMinePC on 2/14/2021.
//

#ifndef OPENGLPROJECT_TEXTURE_H
#define OPENGLPROJECT_TEXTURE_H

#include <string>
#include "glad/glad.h"
#include "stb_image/stb_image.h"

class Texture {
public:
    Texture(std::string filePath);
    ~Texture();
    void Use(unsigned int slot = 0);
private:
    void CreateTexture(std::string filePath);

private:
    unsigned int m_Texture;
};


#endif //OPENGLPROJECT_TEXTURE_H
