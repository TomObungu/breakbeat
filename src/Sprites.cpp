#include "Game.hpp"

void Game::InitializeSprites()
{
        mSpriteRenderer.mDefaultSprites.clear();

        mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "background",
        ResourceManager::GetTexture("background"),
        vec2(0, 0),
        glm::vec2(1960.178, 1033.901),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false,
        vec2(0,0),
        2
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "background-dots",
        ResourceManager::GetTexture("background-dots"),
        vec2(0, 0),
        vec2(1920, 994.167),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "game-logo",
        ResourceManager::GetTexture("game-logo"),
        vec2(372.256, 193.333),
        vec2(1162.667, 573.998),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "start-button",
        ResourceManager::GetTexture("start-button"),
        vec2(862.230f, 720.000f),
        vec2(195.541f, 73.988f),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "exit-button",
        ResourceManager::GetTexture("exit-button"),
        vec2(889.921f, 824.483f),
        vec2(143.693f, 78.957f),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "start-menu-ua",
        ResourceManager::GetTexture("start-menu-ua"),
        vec2(0, 988.918),
        vec2(1920, 91.082),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

      /* Initialize Sprites for the MAIN_MENU game state*/

    mSpriteRenderer.CreateSprite(
        GameState::MAIN_MENU,
        "background",
        ResourceManager::GetTexture("background"),
        vec2(0, 0),
        glm::vec2(1960.178, 1033.901),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false,
        vec2(0,0),
        2
    );

    mSpriteRenderer.CreateSprite(
        GameState::MAIN_MENU,
        "main-menu-ua",
        ResourceManager::GetTexture("main-menu-ua"),
        vec2(-0.866, 988.918),
        vec2(1920.866, 91.082),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::MAIN_MENU,
        "main-menu-settings-button",
        ResourceManager::GetTexture("main-menu-settings-button"),
        vec2(448.689, 571.618),
        vec2(447.212, 264.223),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default-3D"),
        true
    );

    mSpriteRenderer.CreateSprite(
        GameState::MAIN_MENU,
        "main-menu-chart-editor-button",
        ResourceManager::GetTexture("main-menu-chart-editor-button"),
        vec2(1024.394, 208.425),
        vec2(447.212, 264.223),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default-3D"),
        true
    );

    mSpriteRenderer.CreateSprite(
        GameState::MAIN_MENU,
        "main-menu-chart-selection-button",
        ResourceManager::GetTexture("main-menu-chart-selection-button"),
        vec2(448.394, 208.425),
        vec2(447.212, 264.223),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default-3D"),
        true
    );

    mSpriteRenderer.CreateSprite(
        GameState::MAIN_MENU,
        "main-menu-back-button",
        ResourceManager::GetTexture("main-menu-back-button"),
        vec2(1024.394, 571.618),
        vec2(447.212, 264.223),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default-3D"),
        true
    );
}

Sprite* Game::GetSprite(GameState gameState, string name)
{
    // Simplify Getting sprite without the need to write out the entire line
    return mSpriteRenderer.mCurrentlyRenderedSprites[gameState][name];
}

Sprite* Game::GetDefaultSprite(GameState gameState, string name)
{
    // Simplify Getting sprite without the need to write out the entire line
    return mSpriteRenderer.mDefaultSprites[gameState][name];
}

void Game::LoadDefaultSprites(GameState gameState)
{
    mSpriteRenderer.mCurrentlyRenderedSprites[gameState].clear();

    for (auto& [key, sprite] : mSpriteRenderer.mDefaultSprites[gameState])
    {
        // Copy default sprite and reset its state
        Sprite* defaultSprite = sprite; 
        defaultSprite->ResetTransformations(); // Reset scale, rotation, etc.
        mSpriteRenderer.mCurrentlyRenderedSprites[gameState][key] = defaultSprite;
    }
}

