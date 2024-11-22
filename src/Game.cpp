#include "Game.hpp"

Game::Game() : 
    mWindow(Window())
{
}

GUIRenderer* Renderer;
GUIRenderer* AnimRenderer;

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

void Game::Initialize()
 {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Set up orthgraphic projection matrix
    mat4 projection = glm::ortho(0.0f, static_cast<float>(mWindow.GetWindowWidth()),
        static_cast<float>(mWindow.GetWindowHeight()), 0.0f, -1.0f, 1.0f);
    // load shaders
    ResourceManager::LoadShader("\\shaders\\DefaultVertexShader.glsl", "\\shaders\\DefaultFragmentShader.glsl", "default");
    ResourceManager::GetShader("default").Use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("default").Use().SetInteger("image", 0);
    Renderer = new GUIRenderer(ResourceManager::GetShader("default"));
    // configure shaders
    ResourceManager::LoadShader("\\shaders\\BackgroundVertexShader.glsl","\\shaders\\DefaultFragmentShader.glsl", "background");
    ResourceManager::GetShader("background").Use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("background").Use().SetInteger("image", 0);
    AnimRenderer = new GUIRenderer(ResourceManager::GetShader("background"));
    // load textures
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-dots-dots-cropped.png",true,"background-dots");
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-arrows-squares-edit-cropped.png",true,"background");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-logo-2x-new.png", true, "game-logo");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-start-button.png", true, "start-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-exit-button.png", true, "exit-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-user-navigation-assist.png", true, "start-menu-ua");
}

void Game::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Ensure alpha is set to 1.0f for solid background
    glClear(GL_COLOR_BUFFER_BIT);

    float timeValue = (SDL_GetTicks() / 1000.0f);

    // Draw Background
    AnimRenderer->Draw(
        ResourceManager::GetTexture("background"),
        vec2(0, 0),
        glm::vec2(1960.178, 1033.901)
    );

    Renderer->Draw(ResourceManager::GetTexture("background-dots"),
        vec2(0,0),
        vec2(1920, 994.167)
    );

    // Draw Logo
    Renderer->Draw(
        ResourceManager::GetTexture("game-logo"),
        vec2(372.256 - 2 * sin(timeValue * 10), 193.333 - 2 * sin(timeValue * 10)),
        vec2(1162.667 + 4 * sin(timeValue * 10), 573.998 + 4 * sin(timeValue * 10))
    );

    // Draw Start Button
    Renderer->Draw(
        ResourceManager::GetTexture("start-button"),
        vec2(862.230f, 720.000f), 
        vec2(195.541f, 73.988f),
        0,
        vec3(1, 1, -abs(sin(timeValue * 0.75))+1)
    );

    // Draw Exit Button
    Renderer->Draw(
        ResourceManager::GetTexture("exit-button"),
        vec2(889.921f, 824.483f), 
        vec2(143.693f, 78.957f)
    );

    // Draw User Navigation Assist
    Renderer->Draw(
        ResourceManager::GetTexture("start-menu-ua"),
        vec2(0, 988.918), // Adjust Y position if needed
        vec2(1920, 91.082)
    );

    ResourceManager::GetShader("background").SetFloat("time",-timeValue,true);
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
    mWindow.Initialize();
    Initialize();
    // Main loop for the game   
    while (!mWindow.GetWindowClosedBoolean())
    {
         // Handle input and window events
        ProcessEvents(); 
        Render();

        // Update the window with OpenGL
        SDL_GL_SwapWindow(mWindow.GetWindow());  
    }
}
