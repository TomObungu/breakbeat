#include "Mouse.hpp"
#include "Game.hpp"

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

void Mouse::Update(SDL_Event& event, const Window& window)
{
    float mouseX = static_cast<float>(event.motion.x);
    float mouseY = static_cast<float>(event.motion.y);

    float vpX = static_cast<float>(window.GetViewportX());
    float vpY = static_cast<float>(window.GetViewportY());
    float vpW = static_cast<float>(window.GetViewportW());
    float vpH = static_cast<float>(window.GetViewportH());

    // Convert to normalized viewport space
    float normalizedX = (mouseX - vpX) / vpW;
    float normalizedY = (mouseY - vpY) / vpH;

    normalizedX = glm::clamp(normalizedX, 0.0f, 1.0f);
    normalizedY = glm::clamp(normalizedY, 0.0f, 1.0f);

    // Convert to virtual resolution (1920x1080)
    float virtualX = normalizedX * ::VIRTUAL_WIDTH;
    float virtualY = normalizedY * ::VIRTUAL_HEIGHT;

    mPosition = vec2(virtualX, virtualY);
}

void Mouse::DrawMouse()
{
    mShader.Use();

    glm::mat4 model(1.0f);

    // Move to mouse position
    model = glm::translate(model, glm::vec3(mPosition, 0.0f));

    // Scale around center
    model = glm::scale(
        model,
        glm::vec3(mSize * mCurrentScale, 1.0f)
    );

    mShader.SetMatrix4("model", model);
    mShader.SetVector3f("color", mColor);

    GLint uniformLocation = glGetUniformLocation(mShader.ID, "image");
    if (uniformLocation == -1) {
        std::cerr << "Uniform 'image' not found in shader\n";
        return;
    }

    glUniformHandleui64ARB(uniformLocation, mTexture.handle);

    glBindVertexArray(mVertexArrayObject);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 6);
    glBindVertexArray(0);
}


vec2 Mouse::GetMouseCoordinate() const
{
    return mPosition;
}

vec2 Mouse::GetMouseSize()
{
    return mSize;
}

