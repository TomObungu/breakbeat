#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer()
{
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->mVertexArrayObject);
}

void SpriteRenderer::Initialize()
{
    GLuint vertexBufferObject;
    float vertices[] = {
        // Position       // Tex Coords
        0.0f, 1.0f,      0.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 0.0f,
        0.0f, 0.0f,      0.0f, 0.0f,

        0.0f, 1.0f,      0.0f, 1.0f,
        1.0f, 1.0f,      1.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 0.0f
    };

    glGenVertexArrays(1, &this->mVertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(this->mVertexArrayObject);
    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    // Texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

Sprite* SpriteRenderer::CreateSprite(GameState gameState, string name, Texture& texture, vec2 position, vec2 size, float rotate, vec3 color, Shader& shader, bool perspective, vec2 texturePositon, float textureScale)
{
    // Create a pointer to a new Sprite instance
    auto sprite = new Sprite(texture, position, size, rotate, color, shader, perspective, texturePositon, textureScale);

    // Store the pointer in the default sprite hash table
    GLuint& VAO = this->mVertexArrayObject;
    sprite->mVertexArrayObject = VAO;
    mDefaultSprites[gameState][name] = sprite;

    // Return the raw pointer for convenience if needed
    return mDefaultSprites[gameState][name];
}

void SpriteRenderer::DrawSprites(GameState gameState)
{
    for (auto& [key, sprite] : mCurrentlyRenderedSprites[gameState])
    {
        sprite->Draw(); // Use sprite directly; no need to dereference a raw pointer
    }
}

void SpriteRenderer::LoadDefaultSprites(GameState gameState)
{
    for (auto& [key, sprite] : mDefaultSprites[gameState])
    {
        // Use the copy constructor to create a copy of the sprite
        mCurrentlyRenderedSprites[gameState][key] = sprite;
    }
}

