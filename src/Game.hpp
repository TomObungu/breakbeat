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
#include <iomanip>

#include <algorithm>
#include <iterator>

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
using std::setprecision;
using std::regex;
using std::smatch;

using namespace irrklang;

struct NoteColumn {
    // Timing variables
    float hitTime;                    // Time the regular note was hit
    float longNoteHitTime;            // Time the long note head was hit
    float releaseTime;                // Time for releasing the note
    float hitDifference;              // Difference between hit time and target time
    float longNoteHitDifference;
    float releaseDifference;          // Difference between release time and target release time
    float noteTimeIndex;              // Index for regular notes
    float longNoteTimeIndex;          // Index for long note heads
    float longNoteRenderTimeIndex;    // Index for rendering long note heads
    float releaseTimeRenderTimeIndex; // Index for rendering release times
    float releaseTimeIndex;           // Index for release times
    float renderTimeIndex;            // Index for rendering notes

    // Position and visual properties
    string noteName;            // Unique name for the note column
    float xPos;                       // X-axis position of the note column
    float longNoteOriginalHeight;     // Original height of the long note body

    // Time vectors
    vector<float> hitTimes;           // Times to hit regular notes
    vector<float> releaseTimes;       // Times to release long notes
    vector<float> longNoteHitTimes;   // Times to hit long note heads
    vector<float> renderTimes;        // Times to render notes
    vector<float> releaseRenderTimes; // Times to render release components
    vector<float> longNoteRenderTimes;// Times to render long note heads

    // Flags for state management
    bool hitNote;                     // Indicates if a regular note was hit
    bool hitLongNote;                 // Indicates if a long note was hit         
    bool isKeyHeld;                   // Indicates if the key is being held

    // Shrinking logic variables
    float shrinkStartTime;            // Time when shrinking starts
    float shrinkDuration;             // Duration for shrinking the long note body
};

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

    bool ParseDifficultyFile();
    
    void RenderNotes();

    void RenderNote(NoteColumn&);

    void RegisterHit(NoteColumn& noteColumn);

    void HandleHitRegistration(SDL_Event& event);
    
    void HandleHitRelease(SDL_Event& event);

    void UpdateLongNoteState(NoteColumn& noteColumn);
    
    void UpdateScoreLongNotes(NoteColumn& noteColumn);
    
    void UpdateScoreRelease(NoteColumn& noteColumn);

    void HandleMissedHitRegistration();

    void HandleLongNoteRelease(NoteColumn& event);

    void UpdateGameplayStatisticsText();

    void UpdateScore(NoteColumn& noteColumn);

    void StartSongWithAdjustedTiming();
    
    void UpdateGameplayState();

    void UpdateHealthBar();

	void CreateNewChart();

    void InitializeMainGameplay();

    void PreloadAudio();

    void HandleMainGameplay();

    void LoadBackgroundImage();

    void GetCurrentChartDirectories();

    void UpdateChartSelectionImage();

    void InitializeChartEditor();

    void GetChartMetadata();

    void HandleChartEditor();

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

    float mReceptorSize;
    float mScrollSpeed;

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
    ISoundSource* mSongSource = nullptr;

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

    string mCurrentChartFile = "";
    string mCurrentChartImageFile = "";
    string mCurrentChartAudioFile = "";
    string mCurrentSongName = "";
    string mCurrentSongDifficulty = "";
    string mCurrentSongBPM = "";
    unsigned mCurrentSongDuration;
    int mAudioDuration;

    float mSongStartTime = 0;
    float mTimeElapsed = 0;
    float mDelayStartTime = 0;
    float mNegativeOffset = 0;
    float mTimeTakenToFall = 0;

    float mAccuracy = 0;
    float mScore = 0;
    float mMaximumPossibleScore = 0;
    
    int mFlawlessCount = 0;
    int mPerfectCount = 0;
    int mGreatCount = 0;
    int mGoodCount = 0;
    int mBadCount = 0;
    int mMissCount = 0;

    int mHealth = 100;

    NoteColumn firstColumn = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "main-gameplay-left-note",
    581.936, 0,
    {},
    {},
    {},
    {}, {}, {}, false, false, false, 0, 0 };
    NoteColumn secondColumn = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "main-gameplay-down-note",
    765.423, 0,
    {},
    {},
    {},
    {}, {}, {}, false, false, false, 0, 0 };
    NoteColumn thirdColumn = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "main-gameplay-up-note",
    949.361, 0,
    {},
    {},
    {},
    {}, {}, {},false, false, false, 0, 0 };
    NoteColumn fourthColumn = {
    0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    "main-gameplay-right-note",
    1138.061, 0,
    {},
    {},
    {},
    {}, {}, {},false, false, false, 0, 0 };
    vector<NoteColumn> mNoteColumns
    {
    };

    bool mWaitingForGameplayStart = true;
    Uint32 mGameplayStartTime = 0;
    const Uint32 mGameplayDelay = 1000; // 500ms delay before gameplay starts
    Uint32 mScheduledSongStartTime = 0; // Stores when the song should start
    float mAudioStartTime = 0;
    float mAudioDelay = 50;



	bool mSongPlaying = false;
    bool mSongStarted = false;
    bool mStartGame = true;

    bool mGameActive = false;

    bool mAddingSprites = false;
    bool mPlayHoverAnimation = false;

    
};
    
#endif