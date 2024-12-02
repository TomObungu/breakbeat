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

#include <unordered_map>
#include <map>
#include <vector>

using std::unordered_map;
using std::vector;

class Game
{
public:
    void Initialize();
    void Run();
    void ProcessEvents();
    void Update();
    void Render();
    void HandleWindowEvent(SDL_Event&);

	double mDeltaTime;
	double mLastFrame;

    void CalculateDeltaTime();

    void InitMenu();

    Sprite* GetSprite(GameState, string);
    void UpdateSprites(GameState);
    void LoadDefaultSprites(GameState gameState);

    void CheckForTransitionState();
    void TransitionToGameState(GameState newGameState);
    string GetGLErrorString(GLenum error);
    void CheckGLErrors(const std::string& context = "");
    void Transition(GameState newGameState);


    Game();
private:
    // Declare mWindow as a member variable
    GameState mCurrentGameState = GameState::START_MENU;
    Window mWindow;
    SpriteRenderer mSpriteRenderer;

    int mMenuChoice;                 // Persistent menu choice index
    vector<Sprite*> mMenuChoices;    // Store menu sprite choices
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