#include "Game.hpp"

Game::Game() : 
    mWindow(Window())
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
                    mWindow.ToggleFullscreen();
                break;

            default:
                break;
        }
    }
}

void Game::HandleWindowEvent(SDL_Event& event)
{
    // Check if the event is a window resize event and if resize mode is enabled
    switch(event.window.event)
    {
        case(SDL_WINDOWEVENT_RESIZED):
            mWindow.HandleWindowResize(event);
        break;
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
