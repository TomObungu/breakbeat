#include "Mouse.hpp"

Mouse::Mouse()
{
}

Mouse::~Mouse()
{
    // Clean up OpenGL objects
    if (this->mVertexArrayObject != 0)
    {
        glDeleteVertexArrays(1, &this->mVertexArrayObject);
    }
}

void Mouse::InitializeMouse()
{
    GLuint vertexBufferObject;
    float vertices[] = 
    {
        // Position       // Tex Coords
        0.0f, 1.0f,      0.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 0.0f,
        0.0f, 0.0f,      0.0f, 0.0f,

        0.0f, 1.0f,      0.0f, 1.0f,
        1.0f, 1.0f,      1.0f, 1.0f,
        1.0f, 0.0f,      1.0f, 0.0f
    };

    // Set up 2D VAO/VBO
    glGenVertexArrays(1, &this->mVertexArrayObject);
    glGenBuffers(1, &vertexBufferObject);

    glBindVertexArray(this->mVertexArrayObject);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObject);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Position attribute
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_TRUE, 4 * sizeof(float), (void*)0);
    // Texture coordinate attribute
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_TRUE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    // Unbind VAO and VBO
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (this->mVertexArrayObject == 0) {
    std::cerr << "VAO not initialized. Call InitializeMouse() first." << std::endl;
    return;
    }

    this->mShader = ResourceManager::GetShader("cursor");
    if (this->mShader.ID == 0) {
        std::cerr << "Failed to load shader: cursor" << std::endl;
        return;
    }

    this->mTexture = ResourceManager::GetTexture("cursor");
    if (mTexture.handle == 0) {
        std::cerr << "Failed to load texture: cursor" << std::endl;
        return;
    }
}

void Mouse::Update(SDL_Event& event)
{
    const float& xpos{ static_cast<float>(event.motion.x) };
    const float& ypos{ static_cast<float>(event.motion.y) };
    mPosition = vec2(xpos,ypos);
}

void Mouse::DrawMouse()
{
    this->mShader.Use();
    mat4 model = mat4(1.0f);

    model = translate(model, vec3(mPosition, 0.0f));
    model = glm::translate(model, vec3((mSize* mCurrentScale / 2.0f, 0.0f))); // Center sprite
    model = glm::scale(model, vec3(mSize * mCurrentScale, 1.0f)); // Scale to match size
    model = glm::translate(model, vec3((-mSize* mCurrentScale / 2.0f, 0.0f)));

    this->mShader.SetMatrix4("model", model);
    this->mShader.SetVector3f("color", mColor);
    
    GLint uniformLocation = glGetUniformLocation(this->mShader.ID, "image");

    if (uniformLocation == -1) {
        std::cerr << "Uniform 'image' not found in shader" << std::endl;
        return;
    }

    // Pass the sprite's texture handle to the shader
    glUniformHandleui64ARB(uniformLocation, mTexture.handle);
    
    // Draw the sprite
    glBindVertexArray(this->mVertexArrayObject);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    glBindVertexArray(0);
}

vec2 Mouse::GetMouseCoordinate()
{
    return mPosition;
}

vec2 Mouse::GetMouseSize()
{
    return mSize;
}

