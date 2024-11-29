#ifndef SPRITE_HPP
#define SPRITE_HPP

#include <SDL.h>
#include "ResourceManager.hpp"

using glm::radians;
using glm::perspective;

class Sprite 
{
public:
    // Constructor
    // Remove the default arguments for previous parameters
    Sprite(Texture& texture, vec2 position, vec2 size, float rotate, vec3 color,Shader& shader, bool perspective = false,  vec2 texturePositon = vec2(0,0), float textureScale = 1);

    Sprite(const Sprite& other);

    GLuint mVertexArrayObject;

    //  Draw method

    // Utility functions
    void Draw();
    void Move(vec2 pixels);
    void Rotate(vec3 orientation, float angle);
    void MoveTextureCoordinate(vec2 pixels);
    void Scale(float scale);

    // Setters
    void SetPosition(const vec2& position);
    void SetSize(const vec2& size);
    void SetRotation(float rotate);
    void SetColor(const vec3& color);
    void SetShader(Shader& shader);
    void SetTextureScale(float scale);
    
    // Animation functions
    void Flash(vec3 color, float time);
    void SetFlash(bool state, vec3 color, float time);

    void MoveTo(vec2 coordinate, float time);
    void SetMoveTo(bool state, vec2 coordinate, float time);

    // Getters
    vec2 GetPosition() const;
    vec2 GetSize() const;
    float GetRotation() const;
    vec3 GetColor() const;
    Shader& GetShader() const;

    void Update(float deltaTime);

    bool IsAnimationComplete();
    void SetAnimationComplete(bool state);


    // Additional member functions specific to Sprite...
private:
    Texture& mTexture;
    vec2 mTexturePosition;
    float mTextureScale;
    vec2 mPosition;
    vec2 mSize;
    float mRotation;
    vec3 mColor;
    Shader& mShader;
    bool mPerspective;

    // Universal update vairable to handle sprite state updates
    bool mHasUpdated;
    float mCurrentTime;
    float mTotalTime;

    // Animation state varibles
    vec2 mStartCoordinate;
    vec2 mEndCoordinate;
    int mDistanceBetween;
    vec2 mIncrement;
    bool mIsMovingTo;
};

#endif // SPRITE_HPP