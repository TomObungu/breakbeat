#ifndef GAME_HPP
#define GAME_HPP

#include "Window.hpp"

namespace
{
    inline constexpr int WindowWidth { 800 };
    inline constexpr int WindowHeight { 600 };
}

class Game
{
public:
    void ToggleFullscreen();
    void Run();
    void ProcessEvents();
    Game();
private:
    // Declare mWindow as a member variable
    Window mWindow;
    bool mIsFullscreen;
    bool mResizeMode;

};

#endif