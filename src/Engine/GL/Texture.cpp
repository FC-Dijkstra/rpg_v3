#include <iostream>
using namespace std;
#include "../../lib/glad/glad.h"
#include "lib/GLFW/glfw3.h"
#include "../../lib/stb_image.h"
#include "Texture.h"

Texture2D::Texture2D()
: width(0), height(0), internalFormat(GL_RGB), imageFormat(GL_RGB), wrapS(GL_REPEAT), wrapT(GL_REPEAT), filterMin(GL_LINEAR), filterMax(GL_LINEAR)
{
    glGenTextures(1, &this->id);
}

void Texture2D::load(const char* textureFilePath)
{
    int width, height, nrComponents;
    unsigned char * data = stbi_load(textureFilePath, &width, &height, &nrComponents, 0);
    if (data) {
        this->generate(width, height, nrComponents, data);
    }
    else {
        std::cout << "Erreur, impossible de charger la texture" << textureFilePath << std::endl;
        stbi_image_free(data);
    }
}

void Texture2D::generate(unsigned int width, unsigned int height, unsigned int components, unsigned char* data)
{
    if (components == 4) {
        this->internalFormat = GL_RGBA;
        this->imageFormat = GL_RGBA;
        stbi_set_flip_vertically_on_load(true);
    }
    else if (components == 1) {
        this->internalFormat = GL_RED;
        this->imageFormat = GL_RED;
    }

    this->width = width;
    this->height = height;

    glBindTexture(GL_TEXTURE_2D, this->id);
    glTexImage2D(GL_TEXTURE_2D, 0, this->internalFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
    //glGenerateMipmap(GL_TEXTURE_2D);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->filterMax);

    glBindTexture(GL_TEXTURE_2D, 0);

    stbi_image_free(data);

    std::cout << "Loaded texture " << std::endl;
}

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, this->id);
}

void Texture2D::unbind() const
{
    glBindTexture(GL_TEXTURE_2D, 0);
}