#include "Game.hpp"
#include <format>

using std::format;

void Game::InitializeFonts()
{
    mTextRenderer.LoadFont("\\fonts\\OpenSans-ExtraBold.ttf",48,"default-48");
    mTextRenderer.LoadFont("\\fonts\\OpenSans-ExtraBold.ttf",24,"default-24");
    mTextRenderer.LoadFont("\\fonts\\OpenSans-ExtraBold.ttf",18,"default-18");
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

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "song-text-1",
        "Song #1",
        vec2(1030.842, 460.287),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "artist-text-1",
        "Artist #1",
        vec2(1031.634, 510.431),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "song-text-2",
        "Song #2",
        vec2(1059.748, 323.983),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "artist-text-2",
        "Artist #2",
        vec2(1060.540, 374.127),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "song-text-3",
        "Song #3",
        vec2(1099.192, 179.243),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "artist-text-3",
        "Artist #3",
        vec2(1099.984, 229.387),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "song-text-4",
        "Song #4",
        vec2(1136.992, 46.164),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "artist-text-4",
        "Artist #4",
        vec2(1137.784, 96.308),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "song-text-5",
        "Song #5",
        vec2(1059.748, 601.635),
        vec3(1.0f),
        "default-48",
        1.0f
    );

     mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "artist-text-5",
        "Artist #5",
        vec2(1060.540, 651.779),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "song-text-6",
        "Song #6",
        vec2(1094.595, 747.443),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "artist-text-6",
        "Artist #6",
        vec2(1095.387, 797.587),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "song-text-7",
        "Song #7",
        vec2(1129.620, 891.209),
        vec3(1.0f),
        "default-48",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "artist-text-7",
        "Artist #7",
        vec2(1131.483, 943.292),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "new-chart-screen-song-name-text",
        "Enter song name:",
        vec2(606.250, 400.971),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "new-chart-screen-artist-name-text",
        "Enter artist name:",
        vec2(606.250, 465.597),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "new-chart-screen-song-bpm-text",
        "Enter song BPM:",
        vec2(606.250, 533.023),
        vec3(1.0f),
        "default-24",
        1.0f
    );

    mTextRenderer.CreateText
    (
        GameState::CHART_EDITOR_SELECTION_MENU,
        "new-chart-screen-chart-image-text",
        "Image : ",
        vec2(1152.000, 578.085),
        vec3(1.0f),
        "default-18",
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