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
    GLuint vertexBufferObject, vertexBufferObject3D;

    // 2D sprite vertex data
    float vertices2D[] = 
    {
        // Position       // Tex Coords
        0.0f, 1.0f,      0.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 0.0f,
        0.0f, 0.0f,      0.0f, 0.0f,

        0.0f, 1.0f,      0.0f, 1.0f,
        1.0f, 1.0f,      1.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 0.0f
    };

    // 3D sprite vertex data (Position + Tex Coords, no normals)
    float vertices3D[] = 
    {
        // Position         // Tex Coords
        0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top-left
        1.0f, 0.0f, 0.0f,   1.0f, 0.0f,  // Bottom-right
        0.0f, 0.0f, 0.0f,   0.0f, 0.0f,  // Bottom-left

        0.0f, 1.0f, 0.0f,   0.0f, 1.0f,  // Top-left
        1.0f, 1.0f, 0.0f,   1.0f, 1.0f,  // Top-right
        1.0f, 0.0f, 0.0f,   1.0f, 0.0f   // Bottom-right
    };

    // Set up 2D VAO/VBO
    glGenVertexArrays(1, &this->mVertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);

    glBindVertexArray(this->mVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2D), vertices2D, GL_STATIC_DRAW);

    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 4 * sizeof(float), (void*)0);
    // Texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Set up 3D VAO/VBO
    glGenVertexArrays(1, &this->mVertexArrayObject3D);
    glGenBuffers(1, &vertexBufferObject3D);

    glBindVertexArray(this->mVertexArrayObject3D);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject3D);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices3D), vertices3D, GL_STATIC_DRAW);

    // Position attribute (vec3)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_TRUE, 5 * sizeof(float), (void*)0);

    // Texture coordinate attribute (vec2)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 5 * sizeof(float), (void*)(3 * sizeof(float)));

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}


Sprite* SpriteRenderer::CreateSprite(GameState gameState, string name, Texture& texture, vec2 position, vec2 size, float rotate, vec3 color, Shader& shader, bool perspective, vec2 texturePosition, float textureScale)
{
    // Create a new Sprite instance
    auto sprite = new Sprite(texture, position, size, rotate, color, shader, perspective, texturePosition, textureScale);

    // Determine whether the VAO is going to used 3D or 2D based on the mPersepctive parameter
    sprite->mVertexArrayObject = perspective ? this->mVertexArrayObject3D : this->mVertexArrayObject;

    // Store the sprite in the appropriate hash table
    mDefaultSprites[gameState][name] = sprite;

    // Return the pointer to the sprite
    return mDefaultSprites[gameState][name];
}

void SpriteRenderer::CreateNote(GameState gameState, string name, Texture& texture, vec2 position, vec2 size, float rotate, vec3 color, Shader& shader, bool perspective, vec2 texturePosition, float textureScale)
{
    // Create a new Sprite instance
    auto sprite = new Sprite(texture, position, size, rotate, color, shader, perspective, texturePosition, textureScale);

    // Determine whether the VAO is going to used 3D or 2D based on the mPersepctive parameter
    sprite->mVertexArrayObject = perspective ? this->mVertexArrayObject3D : this->mVertexArrayObject;

    // Store the sprite in the appropriate hash table
    mNoteBuffer[gameState][name] = sprite;
}

void SpriteRenderer::DrawSprites(GameState gameState)
{
    // Iterate through each sprite in sprite hash table and call its draw function
    for (auto& [key, sprite] : mCurrentlyRenderedSprites[gameState])
    {
        if(sprite != nullptr)
            sprite->Draw(); // Use sprite directly
    }

    for (const auto& [key, note] : mNoteBuffer[gameState])
    {
        note->Draw();
    }
    
}

void SpriteRenderer::LoadDefaultSprites(GameState gameState)
{
    // Iterate through each sprite and copy it to the currently rendered sprites hash table
    for (auto& [key, sprite] : mDefaultSprites[gameState])
    {
        // Use the copy constructor to create a copy of the sprite
        mCurrentlyRenderedSprites[gameState][key] = sprite;
    }
}
