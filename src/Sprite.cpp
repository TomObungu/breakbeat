#include "Sprite.hpp"

// Constructor that initializes sprite properties
Sprite::Sprite(Texture& texture, vec2 position, vec2 size, float rotate, vec3 color,Shader& shader, bool perspective,  vec2 texturePositon, float textureScale)
    : mTexture(texture),
      mTexturePosition(texturePositon),
      mTextureScale(textureScale),
      mPosition(position),
      mSize(size),
      mRotation(rotate),
      mColor(color),
      mShader(shader),
      mPerspective(perspective)
{
    mHasUpdated = true;;
    mStartCoordinate = vec3(0);
    mEndCoordinate = vec3(0);
    mDistanceBetween = 0;
    mIncrement = vec2(0);
    mIsMovingTo = false;
}

// Draw method for Sprite
void Sprite::Draw() 
{
    mat4 model = mat4(1.0f);
    model = translate(model, vec3(mPosition, 0.0f));
    model = translate(model, vec3(0.5f * mSize.x, 0.5f * mSize.y, 0.0f));
    model = glm::rotate(model, glm::radians(mRotation), vec3(0.0f, 0.0f, 1.0f));
    model = translate(model, vec3(-0.5f * mSize.x, -0.5f * mSize.y, 0.0f));
    model = scale(model, vec3(mSize, 1.0f));

    this->mShader.Use();
    this->mShader.SetMatrix4("model", model);
    this->mShader.SetVector3f("color", mColor);

    glActiveTexture(GL_TEXTURE0);
    mTexture.Bind();

    this->mShader.SetVector2f("texturePosition", mTexturePosition);
    this->mShader.SetFloat("textureScale",mTextureScale);

    glBindVertexArray(this->mVertexArrayObject);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    glBindVertexArray(0);
}
 
void Sprite::Move(vec2 pixels)
{
    mPosition += pixels;
}

// More complex rotation function that considers perspective rotation
void Sprite::Rotate(vec3 orientation, float angle) {
    mat4 model = mat4(1.0f);

    if (mPerspective) 
    {
        // Switch to perspective shader
        // This part assumes you have a mechanism to change shaders in the SpriteRenderer
        mat4 view = lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));
        model = rotate(model, glm::radians(angle), orientation);
        this->mShader.SetMatrix4("view", view);
    } else 
    {
        // Use orthographic shader for normal 2D rotation
        model = rotate(model, radians(angle), orientation);
    }

    // Set model matrix within shader to result of the transformation
    this->mShader.SetMatrix4("model", model);
}

void Sprite::MoveTextureCoordinate(vec2 offset)
{
    // Get the current texture position if stored, or initialize to zero
   this->mTexturePosition += offset;
}

void Sprite::SetTextureScale(float scale)
{
    // Get the current texture position if stored, or initialize to zero
   this->mTextureScale = scale;
}

void Sprite::Scale(float scale)
{
    this->mSize *= scale;
}

 // Setters
void Sprite::SetPosition(const vec2& position) {
    mPosition = position;
}

void Sprite::SetSize(const vec2& size) {
    mSize = size;
}

void Sprite::SetRotation(float rotate) {
    this->mRotation = rotate;
}

void Sprite::SetColor(const vec3& color) {
    this->mColor = color;
}

void Sprite::SetShader(Shader& shader) {
    this->mShader = shader;
}

// Getters
vec2 Sprite::GetPosition() const {
    return mPosition;
}

vec2 Sprite::GetSize() const {
    return mSize;
}

float Sprite::GetRotation() const 
{
    return mRotation;
}

vec3 Sprite::GetColor() const 
{
    return mColor;
}

Shader& Sprite::GetShader() const 
{
    return this->mShader;
}

void Sprite::MoveTo(vec2 coordinate, float time) {
    if (mHasUpdated) {
        mStartCoordinate = mPosition;
        mEndCoordinate = coordinate;
        mTotalTime = time;
        mCurrentTime = 0.0f;
        mIsMovingTo = true;
        mHasUpdated = false;  // Mark animation as in-progress
    }
}


void Sprite::SetMoveTo(bool state, vec2 coordinate, float time) 
{
    mIsMovingTo = state;
    if (state) MoveTo(coordinate, time);
}

void Sprite::SetDarken(float time)
{
    if (!mDarkening) 
    {
        mDarkening = true;
        mDarkenTime = time;
        mDarkenStartTime = SDL_GetTicks() / 1000.0f;  // Start time in seconds
        mOriginalColor = mColor;  // Store the current color as starting color
    }
}

void Sprite::Darken()
{
    if (mDarkening) 
    {
        float currentTime = SDL_GetTicks() / 1000.0f;  // Current time in seconds
        float elapsedTime = currentTime - mDarkenStartTime;
        float progress = glm::clamp(elapsedTime / mDarkenTime, 0.0f, 1.0f);

        // Linearly interpolate the color towards black based on progress
        mColor = glm::mix(mOriginalColor, vec3(0.0f), progress);

        // Stop darkening when progress reaches 1.0
        if (progress >= 1.0f) 
        {
            mDarkening = false;
        }
    }
}

void Sprite::SetInvert(float time)
{
    if (!mInverting) 
    {
        mInverting = true;
        mInvertTime = time;
        mInvertStartTime = SDL_GetTicks() / 1000.0f;  // Start time in seconds
        mDarkenedColor = mColor;  // Store the current darkened color
    }
}

void Sprite::Invert()
{
    if (mInverting) 
    {
        float currentTime = SDL_GetTicks() / 1000.0f;  // Current time in seconds
        float elapsedTime = currentTime - mInvertStartTime;
        float progress = glm::clamp(elapsedTime / mInvertTime, 0.0f, 1.0f);

        // Linearly interpolate the color from the darkened state back to the original color
        mColor = glm::mix(mDarkenedColor, mOriginalColor, progress);

        // Stop inverting when progress reaches 1.0
        if (progress >= 1.0f) 
        {
            mInverting = false;
        }
    }
}

void Sprite::Update(float deltaTime) 
{
    if (mIsMovingTo) {
        mPosition += mIncrement * deltaTime;  // Scale increment by deltaTime
        mDistanceBetween -= glm::length(mIncrement * deltaTime);
        if (mDistanceBetween <= 0) {
            mPosition = mEndCoordinate;  // Snap to end position
            mIsMovingTo = false;
            mHasUpdated = true;  // Mark as complete
        }
    }
    
    if (mDarkening)
    {
        Darken();
    }
}


bool Sprite::IsAnimationComplete()
{ 
    return mHasUpdated; 
}