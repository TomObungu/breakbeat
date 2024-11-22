#include "SpriteRenderer.hpp"

SpriteRenderer::SpriteRenderer(Shader& shader)
{
    this->mShader = shader;
    this->Initialize();
}

SpriteRenderer::~SpriteRenderer()
{
    glDeleteVertexArrays(1, &this->mVertexArrayObject);
}

void SpriteRenderer::Initialize()
{
    unsigned int vertexBufferObject;
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

// Draw method in SpriteRenderer (could be overridden in derived classes)
void SpriteRenderer::Draw(Texture &texture, vec2 position, vec2 size, float rotate, vec3 color) {
    mat4 model = mat4(1.0f);
    model = translate(model, vec3(position, 0.0f));
    model = translate(model, vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
    model = glm::rotate(model, glm::radians(rotate), vec3(0.0f, 0.0f, 1.0f));
    model = translate(model, vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));
    model = scale(model, vec3(size, 1.0f));

    this->mShader.Use();
    this->mShader.SetMatrix4("model", model);
    this->mShader.SetVector3f("color", color);

    glActiveTexture(GL_TEXTURE0);
    texture.Bind();

    glBindVertexArray(this->mVertexArrayObject);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    glBindVertexArray(0);
}

void SpriteRenderer::UseShader(Shader&)
{
    this->mShader = mShader;
}