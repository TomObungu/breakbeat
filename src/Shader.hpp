#ifndef SHADER_H
#define SHADER_H

#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::mat4;

using std::string;

// Shader class for handling both vertex and fragment shaders
class Shader
{
public:
    // state
    unsigned int ID; 
    // constructor
    Shader() { }
    // sets the current shader as active
    Shader& Use();
    // compiles the shader from given source code
    void Compile(const char *vertexSource, const char *fragmentSource);
    // utility functions for uniform varibles
    void SetFloat(const char *name, float value, bool useShader = false);
    void SetInteger (const char *name, int value, bool useShader = false);
    void SetVector3f (const char *name, float x, float y, float z, bool useShader = false);
    void SetVector3f (const char *name, const vec3 &value, bool useShader = false);
    void SetMatrix4 (const char *name, const mat4 &matrix, bool useShader = false);
private:
    // checks if compilation or linking failed and if so, print the error logs
    void checkCompileErrors(unsigned int object, std::string type); 
};

#endif