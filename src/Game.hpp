#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"

#include <algorithm>

using std::max;

namespace
{
    inline constexpr int WindowWidth { 800 };
    inline constexpr int WindowHeight { 600 };
    inline constexpr int MinWindowWidth  { 800 };
    inline constexpr int MinWindowHeight { 600 };
}

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

};

#endif