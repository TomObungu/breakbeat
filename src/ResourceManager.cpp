#include "ResourceManager.hpp"

#include <iostream>
#include <sstream>
#include <fstream>
#include <stdlib.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Instantiate static variables

std::map<std::string, Texture>    ResourceManager::Textures;
std::map<std::string, Shader>       ResourceManager::Shaders;

Shader& ResourceManager::LoadShader(const char *vertexShaderPath, const char *fragmentShaderPath, string name)
{
    Shaders[name] = loadShaderFromFile((fs::current_path().string() + vertexShaderPath).c_str(),
        (fs::current_path().string() + fragmentShaderPath).c_str());
    return Shaders[name];
}

Shader& ResourceManager::GetShader(std::string name)
{
    return Shaders[name];
}

Texture& ResourceManager::LoadTexture(const char *file, bool alpha, string name)
{
    Textures[name] = loadTextureFromFile((fs::current_path().string() + file).c_str(), alpha);
    return Textures[name];
}

Texture& ResourceManager::GetTexture(string name)
{
    return Textures[name];
}

void ResourceManager::Clear()
{
    // (properly) delete all shaders	
    for (auto iter : Shaders)
        glDeleteProgram(iter.second.ID);
    // (properly) delete all textures
    for (auto iter : Textures)
        glDeleteTextures(1, &iter.second.ID);
}

Shader ResourceManager::loadShaderFromFile(const char* vertexShaderPath, const char *fragmentShaderPath)
{
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    try
    {
        // open files
        std::ifstream vertexShaderFile(vertexShaderPath);
        std::ifstream fragmentShaderFile(fragmentShaderPath);
        std::stringstream vertexShaderStringStream, fragmentShaderStringStream;
        // read file's buffer contents into streams
        vertexShaderStringStream << vertexShaderFile.rdbuf();
        fragmentShaderStringStream << fragmentShaderFile.rdbuf();
        // close file handlers
        vertexShaderFile.close();
        fragmentShaderFile.close();
        // convert stream into string
        vertexCode = vertexShaderStringStream.str();
        fragmentCode = fragmentShaderStringStream.str();
    }   
    catch (std::exception exception)
    {
        std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
    }
    const char *vertexShaderCode = vertexCode.c_str();
    const char *fragmentShaderCode = fragmentCode.c_str();
    // 2. now create shader object from source code
    Shader shader;
    shader.Compile(vertexShaderCode, fragmentShaderCode);
    return shader;
}

Texture ResourceManager::loadTextureFromFile(const char *file, bool alpha)
{
    // create texture object
    Texture texture;
    if (alpha)
    {
        texture.textureFormat = GL_RGBA;
        texture.imageFormat = GL_RGBA;
    }
    // load image
    int width, height, nrChannels;
    unsigned char* data = stbi_load(file, &width, &height, &nrChannels, 0);
    // now generate texture
    if (!data) {
    std::cerr << "Failed to load texture from " << file << std::endl;
    }
    texture.Generate(width, height, data);
    // and finally free image data
    stbi_image_free(data);
    return texture;
}