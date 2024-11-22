/*

This is the header file for the Game.cpp which is responsible
for the uber glass in which all aspects of the adaptation are 
integrated in 

*/

#ifndef GAME_HPP
#define GAME_HPP

enum class GameState {
    START_MENU,
    GAMEPLAY,
    PAUSE_MENU,
    OPTIONS_MENU,
    // Add more states as needed
};

// Include the Window.hpp file to allow creation of a Window object
#include "Window.hpp"
#include <unordered_map>
#include <vector>
#include <memory>
#include "ResourceManager.hpp"
#include "Sprite.hpp"

#include <vector>
#include <memory> // For smart pointers

class Game
{
public:
    void Initialize();
    void Run();
    void Update();
    void ProcessEvents();
    void Render();
    void HandleWindowEvent(SDL_Event&);
    Game();
private:
    // Declare mWindow as a member variable
    GameState currentState;
    Window mWindow;
    std::unordered_map<GameState, std::vector<std::unique_ptr<Sprite>>> spriteGroups;
};

#endif