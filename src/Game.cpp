#include "Game.hpp"

Game::Game() : 
    mWindow(Window()),
    mIsFullscreen { true },
    mResizeMode { false },
    mFirstTimeWindowed { true }
{
}

void Game::ProcessEvents()
{
    SDL_Event& event = mWindow.GetWindowEvent();
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                mWindow.SetWindowClosedBoolean(true);
                break;

            case SDL_WINDOWEVENT:
                HandleWindowEvent(event);
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_F11) 
                    ToggleFullscreen();
                break;

            default:
                break;
        }
    }
}

#include <SDL.h>

void Game::HandleWindowEvent(const SDL_Event& event)
{
    // Check if the event is a window resize event and if resize mode is enabled
    if (event.window.event == SDL_WINDOWEVENT_RESIZED && mResizeMode)
    {
        int newWidth = event.window.data1;
        int newHeight = event.window.data2;

        // Clamp the width and height to the maximum values
        if (newWidth < ::MinWindowWidth || newHeight < ::MinWindowHeight)
        {
            newWidth = max(newWidth, ::MinWindowWidth);
            newHeight = max(newHeight, ::MinWindowHeight);
            
            // Optionally, resize the window to the maximum allowed size
            SDL_SetWindowSize(mWindow.GetWindow(), newWidth, newHeight);
        }

        // Update the last windowed size and viewport
        mWindow.SetLastWindowedSize(newWidth, newHeight);
        mWindow.UpdateViewport(newWidth, newHeight);
    }
}

void Game::ToggleFullscreen()
{
    mIsFullscreen = !mIsFullscreen;
    mResizeMode = !mResizeMode;

    if (mIsFullscreen)
    {
        // Enter fullscreen mode
        SDL_SetWindowFullscreen(mWindow.GetWindow(), SDL_WINDOW_FULLSCREEN);
    }
    else
    {
        // Exit fullscreen mode, set windowed mode
        SDL_SetWindowFullscreen(mWindow.GetWindow(), 0);
        
        // Adjust viewport to the last windowed size
        auto [width, height] = mWindow.GetLastWindowedSize();
        mWindow.UpdateViewport(width, height);

        // Center the window only the first time it enters windowed mode
        if (mFirstTimeWindowed)
        {
            SDL_SetWindowPosition(mWindow.GetWindow(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
            mFirstTimeWindowed = false; // Set to false after the first-time centering
        }
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
