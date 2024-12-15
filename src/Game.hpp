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
#include "Menu.hpp"
#include "TextRenderer.hpp"
#include "Mouse.hpp"
#include <unordered_map>
#include <map>
#include <vector>
#include <format>

using std::unordered_map;
using std::vector;
using std::format;

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

	double mDeltaTime;
	double mLastFrame;

    void CalculateDeltaTime();


    Sprite* GetSprite(GameState, string);
    Sprite* GetDefaultSprite(GameState gameState, string name);
    string GetCollidingSprite(GameState);
    void UpdateSprites(GameState);
    void LoadDefaultSprites(GameState gameState);

    void CheckForTransitionState();
    void TransitionToGameState(GameState newGameState);
    string GetGLErrorString(GLenum error);
    void CreateMenu(GameState, vector<Sprite*>, bool, string);
    Menu* GetMenu(GameState, string);
    void CheckGLErrors(const std::string& context = "");
    void Transition(GameState newGameState);

    void InitializeSprites();

    void InitializeMenus();

    void InitializeTextures();

    Game();
private:
    // Declare mWindow as a member variable
    GameState mCurrentGameState = GameState::START_MENU;
    Window mWindow;

    Mouse* mMouse;
    
    SpriteRenderer mSpriteRenderer;

    TextRenderer *Text;

    // Store menu class hash table
    unordered_map<GameState, unordered_map<string, Menu*>> mCurrentMenus;
    
    float mSelectionDelay = 200;     // Minimum delay between inputs in milliseconds
    Uint32 mLastSelectionTime = 0; 

    bool mTransitioningDark = false;
    bool mTransitioningLight = false;
    bool mAllDark = false;
    bool mAllLight = true;
    bool mHasTransitioned = true;
    GameState mTransitioningGameState = GameState::NOT_TRANSITIONING;
    bool mFirstFrame = true;
    bool mFirstTransitionFrame = true;
};
    
#endif