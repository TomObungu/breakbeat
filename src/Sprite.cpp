#include "Sprite.hpp"

// Constructor that initializes sprite properties
Sprite::Sprite(Texture& texture, vec2 position, vec2 size, float rotate, vec3 color, Shader& shader)
    : SpriteRenderer(shader),  // Call the base class constructor with the shader
      mTexture(texture),
      mPosition(position),
      mSize(size),
      mRotation(rotate),
      mColor(color) 
{
}

// Overridden Draw method for Sprite
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

    glBindVertexArray(this->mVertexArrayObject);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    glBindVertexArray(0);
}
 
// Utility Functions
void Sprite::Move(vec2 pixels) {
    mPosition += pixels;
}

void Sprite::MoveTo(vec2 coordinate, float time) {
    // Here you would implement time-based movement (interpolation)
    vec2 increment = (coordinate - mPosition) / time;
    mPosition += increment;  // Simplified for one update
}

void Sprite::Rotate(float angle) {
    mRotation += angle;
}

// More complex rotation function that might involve switching shaders
void Sprite::Rotate(float x, float y, float z, float angle, bool perspective) {
    mat4 model = mat4(1.0f);

    if (perspective) {
        // Switch to perspective shader
        // This part assumes you have a mechanism to change shaders in the SpriteRenderer
        this->mShader = ResourceManager::GetShader("PerspectiveShader");
        mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
        mat4 view = lookAt(vec3(0.0f, 0.0f, 3.0f), vec3(0.0f), vec3(0.0f, 1.0f, 0.0f));

        model = rotate(model, glm::radians(angle), vec3(x, y, z));

        this->mShader.SetMatrix4("view", view);
        this->mShader.SetMatrix4("projection", projection);
    } else {
        // Use orthographic shader for normal 2D rotation
        model = rotate(model, glm::radians(angle), vec3(x, y, z));
    }

    this->mShader.SetMatrix4("model", model);
}

