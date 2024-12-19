#include "Game.hpp"

void Game::InitializeFonts()
{
    mTextRenderer.LoadFont("C:/Users/deeza/OneDrive/breakbeat/fonts/OpenSans-ExtraBold.ttf",24,"default-24");
    std::cout<<"Initialized fonts"<<'\n';
}

void Game::InitializeTexts()
{
    std::cout<<"Initializing texts!"<<'\n';
    mTextRenderer.mDefaultTexts.clear();

    mTextRenderer.CreateText
    (
        GameState::START_MENU,
        "Hello World Text",
        "Hello! World.",
        vec2(940.0f,540.0f),
        vec3(1.0f),
        "default-24"
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