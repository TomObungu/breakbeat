#include "breakbeat.hpp"

Game::Game() : mWindow(Window(WindowWidth, WindowHeight))
{
     while (!mWindow.getWindowClosedBoolean()) // Check if window is marked as closed
    {
        SDL_Event& event { mWindow.getWindowEvent() };
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                mWindow.setWindowClosedBoolean(true);
        }

    }
}

int main(int argc, char* argv[])
{
    Game game;
}
