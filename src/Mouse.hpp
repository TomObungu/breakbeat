#ifndef MOUSE_HPP
#define MOUSE_HPP

#include "Texture.hpp"
#include "Shader.hpp"
#include "ResourceManager.hpp"
#include "SDL.h"

class Mouse
{
private:
    unsigned int mVertexArrayObject;
    Shader mShader;
    Texture mTexture;
    vec3 mColor = vec3(1.0f);
    vec2 mSize = vec2(9.0f,9.0f);
    vec2 mPosition = vec2(0,0);
    float mCurrentScale = 1;
public:
    void Update(SDL_Event&);
    void InitializeMouse();
    void DrawMouse();
    vec2 GetMouseCoordinate();
    vec2 GetMouseSize();
    Mouse();
    ~Mouse();
};

#endif