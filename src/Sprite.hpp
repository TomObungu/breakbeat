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
    Sprite(Texture& texture, vec2 position, vec2 size, float rotate, vec3 color,Shader& shader, bool perspective = false,  vec2 texturePosition = vec2(0,0), float textureScale = 1, bool isMoving = false);

    GLuint mVertexArrayObject;
    float mCurrentSpeed = 1;
    bool mIsMoving;
    

    //  Draw method
    void Draw();

    // Utility functions

    void Move(vec2 pixels);
    void MovePerSecond(float pixelsPerSecond);
    void Rotate(vec3 orientation, float angle);
    void MoveTextureCoordinate(vec2 pixels);
    vec2 ScreenToWorldSpace(vec2 screenCoord, mat4 view);
    void Scale(float scale);

    // Setters for the sprite attributes
    void SetPosition(const vec2& position);
    void SetSize(const vec2& size);
    void SetTexture(const Texture);
    void SetRotation(float rotate);
    void SetColor(const vec3& color);
    void SetShader(Shader& shader);
    void SetTextureScale(float scale);
    
    /*  Animation functions */
    // Will be used to perform transformations and changes to sprite over time
    void MoveTo(vec2 coordinate, float time);
    void SetMoveTo(bool state, vec2 coordinate, float time);

    // Procedure to darken the sprites color over time
    void SetDarken(bool enable, float darkenTime = 1.0f);  // New method to start/stop darkening
    void Darken();  // Existing method to handle darkening process
    
    // Procedure to brighten the sprutes color from the darkened sate over time
    void SetBrighten(bool enable, float invertTime = 1.0f);  // New method to start/stop inverting
    void Brighten();  // Existing method to handle inversion (lightening

    void SetRotation(bool enable, vec3 orientation = vec3(0,0,1), float rotatingTime = 1.0f, float angle = 180, bool looping = false);
    void SetScale(bool enable, float targetScale, float scaleTime = 1.0f, bool looping = false);

    void SetVelocity(bool enable, float velocity);

    // Getters for the sprite attributes
    vec2 GetPosition() const;
    vec2 GetSize() const;
    float GetRotation() const;
    vec3 GetColor() const;
    Shader& GetShader() const;
    bool GetBrightenState();
    bool GetDarkenState();

    void ResetTransformations();

    // Update function
    void Update(float deltaTime);

    bool IsAnimationComplete();

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
    // Used to determine whether the sprite is being rendererd as a 3D object
    bool mPerspective;

    // Universal update vairable to handle sprite state updates
    bool mHasUpdated;
    float mMoveTime = 1.0f;
    float mMoveStartTime= 0.0f;

    float mCurrentTime;
    float mTotalTime;

    /* Animation state varibles */

    // Start and end coordinates for the MoveTo() function
    vec2 mStartCoordinate;
    vec2 mEndCoordinate;
    int mDistanceBetween;
    vec2 mIncrement;

    // Animation state for MoveTo()
    bool mIsMovingTo;
    float mVelocity;
    

    // Animation state for Rotating the sprite
    bool mIsRotating = false;
    bool mIsLoopRotation;
    float mRotationAngle;
    float mRotationStartTime = 0.0f;
    float mRotationTime = 0.2f;
    vec3 mRotationOrientation = vec3(0,0,1);
    float mStartRotationAngle;

    bool mIsScaling = false;
    float mCurrentScale = 1.0f;
    float mStartScale = 1.0f;
    float mTargetScale = 1.0f;
    float mScaleTime;
    float mScaleStartTime;
    bool mIsLoopScaling;

    // Time varibles for the brighten and darken utility functions();
    // Used to determine start times to time the time elapsed 
    float mDarkenStartTime = 0.0f;
    float mBrightenStartTime = 0.0f;
    float mDarkenTime = 1.0f;
    float mBrightenTime = 1.0f;

    // State varible to indicate when the sprite is becoming darker
    bool mDarkening = false;
    bool mBrightening = false;
    
    // Store the original colors of varibles when they are being darkened/brightened
    // Store the darkest color to lighten from
    // Store the original color to darken from
    vec3 mOriginalColor;
    vec3 mDarkenedColor;

    // State varible to determine when the varible is dark or bright
    bool mDarkened = false;
    bool mBrightened = false;
};

#endif // SPRITE_HPP