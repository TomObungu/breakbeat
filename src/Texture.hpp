#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include <glad/glad.h>

// Texture is able to store and configure a texture in OpenGL.
// It also hosts utility functions for easy management.
class Texture
{
public:
    // holds the ID of the texture object, used for all texture operations to reference to this particular texture
    unsigned int ID;
    uint64_t handle; // Bindless texture handle
    // texture image dimensions
    unsigned int width, height; // width and height of loaded image in pixels
    // texture Format
    unsigned int textureFormat; // format of texture object
    unsigned int imageFormat; // format of loaded image
    // texture configuration
    unsigned int textureWrappingS; // wrapping mode on S axis
    unsigned int textureWrappingT; // wrapping mode on T axis
    unsigned int textureFilteringMinimum; // filtering mode if texture pixels < screen pixels
    unsigned int textureFIlteringMaximum; // filtering mode if texture pixels > screen pixels
    // constructor (sets default texture modes)
    Texture();
    ~Texture(); 
    // generates texture from image data
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    // binds the texture as the current active GL_TEXTURE_2D texture object
    void Bind() const;
    uint64_t GetHandle() const; 
};

#endif