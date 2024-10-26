#include "Game.hpp"

Game::Game() : 
    mWindow(Window(WindowWidth, WindowHeight)),
    mIsFullscreen { true },
    mResizeMode { false }
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

void Game::HandleWindowEvent(const SDL_Event& event)
{
    if (event.window.event == SDL_WINDOWEVENT_RESIZED && mResizeMode)
    {
        int newWidth = event.window.data1;
        int newHeight = event.window.data2;
        mWindow.SetLastWindowedSize(newWidth, newHeight);
        mWindow.UpdateViewport(newWidth, newHeight); 
    }
}

void Game::ToggleFullscreen()
{
    // Toggle fullscreen and resize mode in one step
    mResizeMode   = mIsFullscreen;
    mIsFullscreen = !mIsFullscreen;
    
    // Set window mode based on the fullscreen flag
    SDL_SetWindowFullscreen(mWindow.GetWindow(), mIsFullscreen ? SDL_WINDOW_FULLSCREEN : 0);

    // Update the viewport only if returning to windowed mode
    if (!mIsFullscreen) {
        const auto [width, height] = mWindow.GetLastWindowedSize();
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
