#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <map>
#include <string>
#include <iostream>

#include <glad/glad.h>

#include "Texture.hpp"
#include "Shader.hpp"

using std::map;
using std::cerr;

// A static singleton ResourceManager class that hosts several
// functions to load textures and shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no 
// public constructor is defined (singleton class)

class ResourceManager
{
public:
    // Shaders and textures stored within a hash table
    static map<string, Shader>    Shaders;
    static map<string, Texture> Textures;
    // loads (and generates) a shader program from file loading vertex, fragment 
    static Shader& LoadShader(const char *vertexShaderPath, const char *fragmentShaderPath, string name);
    // retrieves a stored sader
    static Shader& GetShader(string name);
    // loads (and generates) a texture from file
    static Texture& LoadTexture(const char *file, bool alpha, string name);
    // retrieves a stored texture
    static Texture& GetTexture(string name);
    // properly de-allocates all loaded resources
    static void Clear();
private:
    // private constructor, that is we do not want any actual resource manager objects.
    ResourceManager() { }
    // loads and generates a shader from file
    static Shader loadShaderFromFile(const char *vertexShaderFile, const char *fShaderFile);
    // loads a single texture from file
    static Texture loadTextureFromFile(const char *file, bool alpha);
};

#endif