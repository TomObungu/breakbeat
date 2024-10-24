#ifndef BREAKBEAT_HPP
#define BREAKBEAT_HPP

#include "Window.hpp"

namespace
{
    inline constexpr int WindowWidth { 1920 };
    inline constexpr int WindowHeight { 1080 };
}

class Game
{
public:
    Game();
private:
    // Declare mWindow as a member variable
    Window mWindow;
};

#endif