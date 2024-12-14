#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Texture.hpp"
#include "Shader.hpp"
#include "ResourceManager.hpp"
#include "SDL.h"
#include <utility>

class Mouse
{
private:
    unsigned int mVertexArrayObject, mVertexBufferObject;
    Shader mShader;
    Texture mTexture;
    vec2 mSize;
    vec3 mColor;
    vec2 mPosition;
    float mCurrentScale;
public:
    void Update(SDL_Event&);
    void InitializeMouse();
    void DrawMouse();
    // vec2 GetMouseCoordinates();
    Mouse();
};

#endif