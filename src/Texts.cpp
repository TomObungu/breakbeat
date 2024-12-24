#include "Game.hpp"
#include <format>

using std::format;

void Game::InitializeFonts()
{
    mTextRenderer.LoadFont("\\fonts\\OpenSans-ExtraBold.ttf",48,"default-48");
    // std::cout<<"Initialized fonts"<<'\n';
}

void Game::InitializeTexts()
{
    // std::cout<<"Initializing texts!"<<'\n';
    mTextRenderer.mDefaultTexts.clear();

    LoadSettings();

    mTextRenderer.CreateText
    (
        GameState::SETTINGS,
        "scroll-speed-text",
        format("{}",mScrollSpeed),
        vec2(885.98,253.99),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::SETTINGS,
        "receptor-size-text",
        format("{}%",mReceptorSize),
        vec2(885.98,310.99),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::SETTINGS,
        "scroll-direction-text",
        format("{}",mScrollDirection),
        vec2(885.98,377.99),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::SETTINGS,
        "left-keybind-text",
        format("{}",mLeftKeybind),
        vec2(699,465),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::SETTINGS,
        "down-keybind-text",
        format("{}",mDownKeybind),
        vec2(752.18,537),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::SETTINGS,
        "up-keybind-text",
        format("{}",mUpKeybind),
        vec2(664.87,608),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::SETTINGS,
        "right-keybind-text",
        format("{}",mRightKeybind),
        vec2(723.69,681.38),
        vec3(1.0f),
        "default-48",
        1.0f
    );
}

Text* Game::GetText(GameState gameState, string name)
{
    // Simplify Getting Text without the need to write out the entire line
    return mTextRenderer.mCurrentlyRenderedTexts[gameState][name];
}

Text* Game::GetDefaultText(GameState gameState, string name)
{
    // Simplify Getting sprite without the need to write out the entire line
    return mTextRenderer.mDefaultTexts[gameState][name];
}