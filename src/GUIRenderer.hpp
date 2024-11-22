#ifndef GUI_RENDERER_HPP
#define GUI_RENDERER_HPP

#include "Shader.hpp"
#include "Texture.hpp"

#include <glm/glm.hpp>

#include <iostream>

using glm::vec2;
using glm::vec3;
using glm::mat4;
using glm::radians;
using glm::translate;
using glm::scale;

class GUIRenderer
 {
 public:
    void UseShader(Shader&);
    void Draw(Texture& texture, vec2 position, vec2 size = vec2(10.0f,10.0f), float rotate=0.0f, vec3 color = vec3(1.0f));
    GUIRenderer(Shader&);
    ~GUIRenderer();
private:
    Shader mShader;
    unsigned int mVertexArrayObject;
    void Initialize();
};

#endif