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

    mSpriteRenderer.CreateSprite(
        GameState::SETTINGS,
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
        GameState::SETTINGS,
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
        GameState::SETTINGS,
        "settings-menu-ua",
        ResourceManager::GetTexture("settings-menu-ua"),
        vec2(-1.1, 988.918),
        vec2(1920.866, 91.082),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::SETTINGS,
        "settings-menu-text",
        ResourceManager::GetTexture("settings-menu-text"),
        vec2(0, 200),
        vec2(1203.980, 542.850),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::SETTINGS,
        "settings-increment-left-1",
        ResourceManager::GetTexture("settings-increment-left"),
        vec2(808.060, 240.958),
        vec2(44.331, 68.262),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::SETTINGS,
        "settings-increment-left-2",
        ResourceManager::GetTexture("settings-increment-left"),
        vec2(808.060, 301.370),
        vec2(44.331, 68.262),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::SETTINGS,
        "settings-increment-left-3",
        ResourceManager::GetTexture("settings-increment-left"),
        vec2(808.060, 369.703),
        vec2(44.331, 68.262),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::SETTINGS,
        "settings-increment-right-1",
        ResourceManager::GetTexture("settings-increment-right"),
        vec2(1062.076f, 240.958),
        vec2(44.331, 68.262),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::SETTINGS,
        "settings-increment-right-2",
        ResourceManager::GetTexture("settings-increment-right"),
        vec2(1062.076f, 301.370),
        vec2(44.331, 68.262),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::SETTINGS,
        "settings-increment-right-3",
        ResourceManager::GetTexture("settings-increment-right"),
        vec2(1062.076f, 369.703),
        vec2(44.331, 68.262),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
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
        GameState::CHART_EDITOR_SELECTION_MENU,
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
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-selection-menu-ua",
        ResourceManager::GetTexture("chart-editor-selection-menu-ua"),
        vec2(-12.240, 991.539),
        vec2(1944.480, 102.323),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-selection-menu-highlight-1",
        ResourceManager::GetTexture("chart-editor-selection-menu-highlight"),
        vec2(946.962f, 421.652),
        vec2(795.886, 150.255),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-selection-menu-ui-3",
        ResourceManager::GetTexture("chart-editor-selection-menu-ui"),
        vec2(1006.986, 137.932),
        vec2(795.886, 150.255),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-selection-menu-ui-2",
        ResourceManager::GetTexture("chart-editor-selection-menu-ui"),
        vec2(977.394, 278.654),
        vec2(795.886, 150.255),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-selection-menu-ui-4",
        ResourceManager::GetTexture("chart-editor-selection-menu-ui"),
        vec2(1052.574, 0.726),
        vec2(795.886, 150.255),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-selection-menu-ui-5",
        ResourceManager::GetTexture("chart-editor-selection-menu-ui"),
        vec2(977.294, 567.628),
        vec2(795.886, 150.255),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-selection-menu-ui-6",
        ResourceManager::GetTexture("chart-editor-selection-menu-ui"),
        vec2(1006.986, 710.910),
        vec2(795.886, 150.255),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-selection-menu-ui-7",
        ResourceManager::GetTexture("chart-editor-selection-menu-ui"),
        vec2(1045.369, 848.019),
        vec2(795.886, 150.255),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-new-chart-button",
        ResourceManager::GetTexture("chart-editor-new-chart-button"),
        vec2(84.226f, 54.383f),
        vec2(642.458f,419.031f),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
    );
    
    mSpriteRenderer.CreateSprite(
        GameState::CHART_EDITOR_SELECTION_MENU,
        "chart-editor-new-chart-button",
        ResourceManager::GetTexture("chart-editor-new-chart-button"),
        vec2(84.226f, 54.383f),
        vec2(642.458f,419.031f),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false
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

