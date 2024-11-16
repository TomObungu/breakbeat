/*

This is the header file for the Game.cpp which is responsible
for the uber glass in which all aspects of the adaptation are 
integrated in 

*/

#ifndef GAME_HPP
#define GAME_HPP

// Include the Window.hpp file to allow creation of a Window object
#include "Window.hpp"

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
    Window mWindow;
};

#endif