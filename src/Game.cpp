#include "Game.hpp"

Game::Game() : 
    mWindow(Window(WindowWidth, WindowHeight)),
    mIsFullscreen { true },
    mResizeMode { false }
{
}

void Game::ProcessEvents()
{
    SDL_Event& event { mWindow.GetWindowEvent() };
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
            mWindow.SetWindowClosedBoolean(true);

        if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_RESIZED 
            && mResizeMode)
        {
            int newWidth = event.window.data1;
            int newHeight = event.window.data2;
            mWindow.SetLastWindowedWidth(newWidth);
            mWindow.SetLastWindowedHeight(newHeight);
            mWindow.UpdateViewport(newWidth, newHeight); 
        }

        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_F11)
        {
            ToggleFullscreen();
        }
    }
}

void Game::ToggleFullscreen()
{
    mIsFullscreen = !mIsFullscreen;
    mResizeMode = !mResizeMode;
    if (mIsFullscreen && !mResizeMode)
    {
        SDL_SetWindowFullscreen(mWindow.GetWindow(), SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        SDL_SetWindowFullscreen(mWindow.GetWindow(), 0);
        int width = mWindow.GetLastWindowedWidth(), height = mWindow.GetLastWindowedHeight();
        mWindow.UpdateViewport(width, height);
    }
}

void Game::Run()
{
    // Main loop for the game
    while (!mWindow.GetWindowClosedBoolean())
    {
         // Handle input and window events
        ProcessEvents(); 

        // Update the window with OpenGL
        SDL_GL_SwapWindow(mWindow.GetWindow());  
    }
}
