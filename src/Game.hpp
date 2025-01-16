/*

This is the header file for the Game.cpp which is responsible
for the uber glass in which all aspects of the adaptation are 
integrated in 

*/

#ifndef GAME_HPP
#define GAME_HPP

// Include the Window.hpp file to allow creation of a Window object
#include "Window.hpp"
#include "ResourceManager.hpp"
#include "SpriteRenderer.hpp"
#include "tinyfiledialogs.h"
#include <irrklang/irrKlang.h>
#include "Menu.hpp"
#include "TextRenderer.hpp"
#include "Mouse.hpp"
#include <unordered_map>
#include <map>
#include <utility>
#include <vector>
#include <format>
#include <fstream>
#include <sstream>
#include <regex>
#include <string>
#include <array>

#pragma comment(lib, "irrKlang.lib")

using std::unordered_map;
using std::vector;
using std::format;
using std::ifstream;
using std::getline;
using std::stringstream;
using std::to_string;
using std::ostringstream;
using std::ofstream;
using std::make_pair;
using std::array;
using namespace irrklang;

class Game
{
public:
    void Initialize();
    void Run();
    void ProcessEvents();
    void Update();
    void Render();
    void HandleWindowEvent(SDL_Event&);
    void HandleMenuInput(SDL_Event&);
    void HandleKeyboardInput(SDL_Event&);
    void HandleMouseInput(SDL_Event&);
    void UpdateChartSelection();

	double mDeltaTime;
	double mLastFrame;
    
    void CalculateDeltaTime();

    Sprite* GetSprite(GameState, string);
    Sprite* GetDefaultSprite(GameState gameState, string name);
    Sprite* CheckCollidingSprite(GameState);
    Text* CheckCollidingText(GameState);
    void UpdateSprites(GameState);
    void UpdateTexts(GameState);
    void LoadDefaultSprites(GameState gameState);
    
    Text* GetDefaultText(GameState gameState, string name);
    Text* GetText(GameState gameState, string name);

    void CheckForTransitionState();
    void TransitionToGameState(GameState newGameState);
    void CreateMenu(GameState, vector<Sprite*>, bool, string);
    void CreateMenu(GameState, vector<Text*>,bool, string);
    Menu* GetMenu(GameState, string);
    void Transition(GameState newGameState);

    void LoadSettings();
    void UpdateSettings();
    
    void CheckNewChartButton();
    void InitializeChartSelection();
    void PlayCurrentlySelectedChartAudio();
    void HandleChartScrolling(SDL_Event& event);
    void GetCurrentChartDifficulties();
    void HandleDifficultyScrolling(SDL_Event& event);
    void UpdateCurrentChartDifficulties();
    
    void CreateNewChart();

    void InitializeSprites();

    void InitializeMenus();

    void InitializeTextures();

    void InitializeTexts();

    void InitializeFonts();

    Game();
private:
    // Declare mWindow as a member variable
    GameState mCurrentGameState = GameState::START_MENU;
    Window mWindow;

    SpriteRenderer mSpriteRenderer;
    TextRenderer mTextRenderer;
    Mouse* mMouse;
    ISoundEngine* mSoundEngine;
    
    // Store menu class hash table
    unordered_map<GameState, unordered_map<string, Menu*>> mCurrentMenus;
    
    float mSelectionDelay = 200;     // Minimum delay between inputs in milliseconds
    Uint32 mLastSelectionTime = 0; 

    int mReceptorSize;
    int mScrollSpeed;

    string mScrollDirection;

    bool mSelectedSetting = false;
    bool mKeybindMode = false;
    bool mTypingMode = false;
    Text* mCurrentTextBox;
    string mLeftKeybind;
    string mDownKeybind;
    string mUpKeybind;
    string mRightKeybind;

    bool mTransitioningDark = false;
    bool mTransitioningLight = false;
    bool mAllDark = false;
    bool mAllLight = true;
    bool mHasTransitioned = true;
    GameState mTransitioningGameState = GameState::NOT_TRANSITIONING;
    bool mFirstFrame = true;
    bool mFirstTransitionFrame = true;

    bool mShowNewChartScreen = false;
    bool mShowNewDifficultyScreen = false;
    bool mNewChartSpritesOnScreen = false;
    bool mNewDifficultySpritesOnScreen = false;
    bool removingSprites = true;

    string mNewChartAudioPath;
    string mNewChartImagePath;
    string mNewChartSongName;
    string mNewChartArtistName;
    string mNewChartDifficultyName;
    string mNewChartBPM;

    vector<string> mAllCharts;
    vector<string> mAllCurrentChartDifficulties;
    array<string, 7> mCurrentlyPreviewedCharts;
    array<string, 4> mCurrentlyPreviewedDifficulties;
    unsigned mChartPreviewStartIndex = 0; 
    size_t mChartPreviewEndIndex = 0;     
    unsigned mChartDifficultyPreviewStartIndex = 0; 
    size_t mChartDifficultyPreviewEndIndex = 0; 

    bool mAddingSprites = false;
    bool mPlayHoverAnimation = false;
    
};
    
#endif