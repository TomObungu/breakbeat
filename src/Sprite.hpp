#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SpriteRenderer.hpp"
#include "ResourceManager.hpp"

class Sprite : public SpriteRenderer {
public:
    // Constructor
    // Remove the default arguments for previous parameters
    Sprite(Texture& texture, vec2 position, vec2 size, float rotate, vec3 color, Shader& shader);
    
    // Override Draw method
    virtual void Draw();
    void Move(vec2 pixels);
    void MoveTo(vec2 coordinate, float time);
    void Rotate(float angle);
    void Rotate(float x, float y, float z, float angle, bool perspective = false);

    // Additional member functions specific to Sprite...
private:
    Texture& mTexture;
    vec2 mPosition;
    vec2 mSize;
    float mRotation;
    vec3 mColor;
};

#endif // SPRITE_HPP
