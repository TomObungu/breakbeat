#include <iostream>

#include "texture.hpp"


Texture::Texture()
    : width(0), 
    height(0), 
    handle(0),
    textureFormat(GL_RGB), 
    imageFormat(GL_RGB), 
    textureWrappingS(GL_REPEAT), 
    textureWrappingT(GL_REPEAT), 
    textureFilteringMinimum(GL_LINEAR), 
    textureFilteringMaximum(GL_LINEAR)
{
}

void Texture::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->width = width;
    this->height = height;
    // create Texture
    glGenTextures(1, &this->ID);
    glBindTexture(GL_TEXTURE_2D, this->ID);
    glTexImage2D(GL_TEXTURE_2D, 0, this->textureFormat, width, height, 0, this->imageFormat, GL_UNSIGNED_BYTE, data);
    // set Texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, this->textureWrappingS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, this->textureWrappingT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, this->textureFilteringMinimum);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, this->textureFilteringMaximum);
    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
    this->handle = glGetTextureHandleARB(this->ID); // Convert the texture to a unsigned 64 bit interger reference
    glMakeTextureHandleResidentARB(this->handle); // Make the texture reference resident
}

GLuint64 Texture::GetHandle()
{
    return this->handle;
}
