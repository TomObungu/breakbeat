#include "Text.hpp"
#include <iostream>
Text::Text(const string& text, vec2 position, vec3 color, float scale)
    : mText(text), 
    mPosition(position), 
    mColor(color), 
    mScale(scale) 
{
    mOriginalColor = color;
}

void Text::Draw() 
{
    mShader.Use();
    mShader.SetVector3f("textColor", mColor);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->mVertexArrayObject);

    float x = mPosition.x;
    for (const char& c : mText) 
    {
        Character ch = mCharacters[c];
        float xpos = x + ch.Bearing.x;
        float ypos = mPosition.y + (this->mCharacters['H'].Bearing.y - ch.Bearing.y);
        float w = ch.Size.x * mScale;
        float h = ch.Size.y * mScale;

        float vertices[6][4] = 
        {
            {xpos,     ypos + h,    0.0f, 1.0f},
            {xpos + w, ypos,        1.0f, 0.0f},
            {xpos,     ypos,        0.0f, 0.0f},

            {xpos,     ypos + h,    0.0f, 1.0f},
            {xpos + w, ypos + h,    1.0f, 1.0f},
            {xpos + w, ypos,        1.0f, 0.0f}
        };

        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glBindBuffer(GL_ARRAY_BUFFER, this->mVertexBufferObject);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        x += (ch.Advance >> 6) * mScale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

const string& Text::GetText()
{
    return mText;
}

void Text::UpdateText(const std::string& newText) {
    mText = newText;
}

void Text::SetColor(const glm::vec3& color) {
    mColor = color;
}

void Text::SetScale(float scale) {
    mScale = scale;
}

void Text::SetScale(bool enable, float targetScale, float scaleTime, bool looping)
{
    if (!mIsScaling && enable)
    {
        mStartScale = mScale; // Start from the current scale
        mTargetScale = targetScale;
        mScaleTime = scaleTime;
        mScaleStartTime = SDL_GetTicks();
        mIsScaling = true;
        mIsLoopScaling = looping;
    }
}

void Text::SetDarken(bool enable, float darkenTime)
{
    if(!mDarkened || mBrightened && !mDarkening)
    {
        mDarkenTime = darkenTime;
        mOriginalColor = mColor;
        mDarkening = true;
        mDarkenStartTime = SDL_GetTicks();
    }
}

void Text::Darken()
{
    float timeElapsed = SDL_GetTicks() - mDarkenStartTime;
    float progress =  timeElapsed / (mDarkenTime * 1000);
    mColor = mOriginalColor - progress;
    if(mColor.x <= 0 && mColor.y <= 0 && mColor.z <= 0 || timeElapsed >= 1000)
    {
        mColor = vec3(0);
        mDarkened = true;
        mDarkening = false;
        mBrightened = false;
    }
}

void Text::SetBrighten(bool enable, float brightenTime)
{
    if(!mBrightened || mDarkened && !mBrightening)
    {
        mBrightenTime = brightenTime;
        mDarkenedColor = mColor;
        mBrightening = true;
        mBrightenStartTime = SDL_GetTicks();
    }
}

void Text::Brighten()
{
    float timeElapsed = SDL_GetTicks() - mBrightenStartTime;
    float progress =  timeElapsed / (mBrightenTime * 1000);
    mColor = mDarkenedColor + progress;
    if( 
     timeElapsed >= 1000
     )
    {
        mColor = mOriginalColor;
        mBrightened = true;
        mBrightening = false;
        mDarkened = false;
    }
}

void Text::Update(float deltaTime) 
{
    // If the sprite is in the darkening state it will call the darken function
    if (mDarkening)
        Darken();

    // If the sprite is the in the brightening state then brighten the function
    if (mBrightening)
        Brighten();

    // If the sprite is fully black it has been darkened
    if(mColor == vec3(0))
        mDarkened = true;

    // If the sprite is fully bright it has been brightened
    if(mColor == vec3(1))
        mBrightened = true;

    // If the sprite is not in any update state it has been fully updated
    if(mDarkened || mBrightened)
    {
        mHasUpdated == true;
    }

    if (mIsScaling)
    {
        float timeElapsed = (SDL_GetTicks() - mScaleStartTime) / 1000.0f; // Convert to seconds
        float progress = timeElapsed / mScaleTime; // Progress as a ratio (0 to 1)

        if (timeElapsed >= mScaleTime && !mIsLoopScaling)
        {
            mIsScaling = false; // Stop scaling if done
            progress = 1.0f;    // Clamp to the final value
        }

        mScale = glm::mix(mStartScale, mTargetScale, progress); // Interpolate between scales
    }
}