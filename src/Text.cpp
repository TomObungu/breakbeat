#include "Text.hpp"
#include <iostream>
Text::Text(const string& text, vec2 position, vec3 color, float scale)
    : mText(text), 
    mPosition(position), 
    mColor(color), 
    mScale(scale) 
{
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
        float xpos = x + ch.Bearing.x * mScale;
        float ypos = mPosition.y + (this->mCharacters['H'].Bearing.y - ch.Bearing.y) * mScale;
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

void Text::UpdateText(const std::string& newText) {
    mText = newText;
}

void Text::SetColor(const glm::vec3& color) {
    mColor = color;
}

void Text::SetScale(float scale) {
    mScale = scale;
}