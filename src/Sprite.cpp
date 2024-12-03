#include "Sprite.hpp"
#include "Window.hpp"

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
    mHasUpdated = true;
    mOriginalColor = color;
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
    mat4 view = mat4(1.0f);

    this->mShader.Use();

    if (mPerspective)
    {
        // Fixed camera position for 3D
        view = glm::translate(mat4(1.0f), glm::vec3(0.0f, 0.0f, -2.0f));
        this->mShader.SetMatrix4("view", view);

        // Compute world position and size
        vec2 worldPos = ScreenToWorldSpace(vec2(mPosition.x * 2.f, mPosition.y * 2.f), view);
        vec2 worldSize = 2.0f * ScreenToWorldSpace(mSize, view);

        model = glm::translate(model, vec3(worldPos.x, worldPos.y, 0.0f)); // Move to world position
        model = glm::translate(model, vec3(worldSize / 2.0f, 0.0f)); // Center sprite
        model = glm::rotate(model, glm::radians(mRotation), vec3(0.0f, 0.0f, 1.0f)); // Rotate around center
        model = glm::translate(model, vec3(-worldSize / 2.0f, 0.0f)); // Translate back
        model = glm::scale(model, vec3(worldSize, 1.0f)); // Scale to match size

        this->mShader.SetMatrix4("model", model);
    }
    else
    {
        // Apply transformations: center, rotate, and scale
        model = translate(model, vec3(mPosition, 0.0f));
        model = translate(model, vec3(0.5f * mSize.x, 0.5f * mSize.y, 0.0f));
        model = glm::rotate(model, glm::radians(mRotation), vec3(0.0f, 1.0f, 0.0f));
        model = translate(model, vec3(-0.5f * mSize.x, -0.5f * mSize.y, 0.0f));
        model = scale(model, vec3(mSize, 1.0f));
    }


    // Set the model matrix
    this->mShader.SetMatrix4("model", model);
    this->mShader.SetVector3f("color", mColor);

    // Texture handling
    glActiveTexture(GL_TEXTURE0);
    mTexture.Bind();

    this->mShader.SetVector2f("texturePosition", mTexturePosition);
    this->mShader.SetFloat("textureScale", mTextureScale);

    // Draw the sprite
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

    model = rotate(model, radians(angle), orientation);

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

    }
}

void Sprite::SetMoveTo(bool state, vec2 coordinate, float time) 
{
    mIsMovingTo = state;
    if (state) MoveTo(coordinate, time);
}

void Sprite::SetDarken(bool enable, float darkenTime)
{
    if(!mDarkened || mBrightened && !mDarkening)
    {
        mDarkenTime = darkenTime;
        mOriginalColor = mColor;
        mDarkening = true;
        mDarkenStartTime = SDL_GetTicks();
    }
}

void Sprite::Darken()
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

// Start or stop the Brightening process
void Sprite::SetBrighten(bool enable, float brightenTime)
{
    if(!mBrightened || mDarkened && !mBrightening)
    {
        mBrightenTime = brightenTime;
        mDarkenedColor = mColor;
        mBrightening = true;
        mBrightenStartTime = SDL_GetTicks();
    }
}

void Sprite::Brighten()
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

// The Update method will call Darken and Brighten as needed
void Sprite::Update(float deltaTime) 
{
    if (mIsMovingTo) {

    }
    
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
    if( (mDarkened || mBrightened) &&
        mIsMovingTo == false)
    {
        mHasUpdated == true;
    }
}

bool Sprite::GetBrightenState()
{
    return mBrightened;
}

bool Sprite::GetDarkenState()
{
    return mDarkened;
}

bool Sprite::IsAnimationComplete()
{
    return mHasUpdated;
}

vec2 Sprite::ScreenToWorldSpace(vec2 screenCoord, mat4 view) 
{
    // NORMALIZED DEVICE COORDINATES (NDC)
    double x = (2.0 * screenCoord.x / 1920) - 1.0;
    double y = 1.0 - (2.0 * screenCoord.y / 1080); // Flip Y axis for NDC

    // Homogeneous clip space
    glm::vec4 screenPos = glm::vec4(x, y, 1.0f, 1.0f); 

    // Perspective projection matrix
    float aspectRatio = static_cast<float>(1920) / 1080;
    mat4 perspectiveProjection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);

    // Transform from NDC to world space
    glm::mat4 viewProjectionInverse = glm::inverse(perspectiveProjection * view);
    glm::vec4 worldPos = viewProjectionInverse * screenPos;

    return glm::vec2(worldPos.x, worldPos.y);
}

