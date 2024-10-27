#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"

#include <algorithm>

using std::max;

class Game
{
public:
    void ToggleFullscreen();
    void Run();
    void ProcessEvents();
    void HandleWindowEvent(const SDL_Event&);
    Game();
private:
    // Declare mWindow as a member variable
    Window mWindow;
    bool mIsFullscreen;
    bool mResizeMode;
    bool mFirstTimeWindowed;
};

#endif