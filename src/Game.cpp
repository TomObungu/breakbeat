#include "Game.hpp"

Game::Game() : 
    mWindow(Window())
{
}

float timeValue;

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
    // configure shaders
    ResourceManager::LoadShader("\\shaders\\BackgroundVertexShader.glsl","\\shaders\\DefaultFragmentShader.glsl", "background");
    ResourceManager::GetShader("background").Use().SetMatrix4("projection", projection);
    ResourceManager::GetShader("background").Use().SetInteger("image", 0);
    // load textures
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-dots-dots-cropped.png",true,"background-dots");
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-arrows-squares-edit-cropped.png",true,"background");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-logo-2x-new.png", true, "game-logo");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-start-button.png", true, "start-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-exit-button.png", true, "exit-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-user-navigation-assist.png", true, "start-menu-ua"); 

    currentState = GameState::START_MENU;

    // Load Sprites
    // Clear previous sprites
    spriteGroups.clear();

    // Initialize sprites for the START_MENU state

    spriteGroups[GameState::START_MENU]["background"] = (std::make_unique<Sprite>(
        ResourceManager::GetTexture("background"),
        vec2(0, 0),
        glm::vec2(1960.178, 1033.901),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("background")
    ));


    spriteGroups[GameState::START_MENU]["background-dots"] = (std::make_unique<Sprite>(
        ResourceManager::GetTexture("background-dots"), 
        vec2(0, 0), 
        vec2(1920, 994.167), 
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default")
    ));


    spriteGroups[GameState::START_MENU]["game-logo"] = (std::make_unique<Sprite>(
        ResourceManager::GetTexture("game-logo"), 
        vec2(372.256, 193.333), 
        vec2(1162.667, 573.998), 
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default")
    ));

    spriteGroups[GameState::START_MENU]["start-button"] = (std::make_unique<Sprite>(
        ResourceManager::GetTexture("start-button"), 
        vec2(862.230f, 720.000f), 
        vec2(195.541f, 73.988f), 
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default")
    ));

    spriteGroups[GameState::START_MENU]["exit-button"] = (std::make_unique<Sprite>(
        ResourceManager::GetTexture("exit-button"), 
        vec2(889.921f, 824.483f), 
        vec2(143.693f, 78.957f), 
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default")
    ));

    spriteGroups[GameState::START_MENU]["start-menu-ua"] = (std::make_unique<Sprite>(
        ResourceManager::GetTexture("start-menu-ua"),
        vec2(0, 988.918),
        vec2(1920, 91.082),
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default")
    ));
}

void Game::Update()
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (currentState == GameState::START_MENU)
    {
        if(state[SDL_SCANCODE_DOWN])
        {
            spriteGroups[currentState]["background"]->Move(vec2(0,1));
        }
        if(state[SDL_SCANCODE_UP])
        {
            spriteGroups[currentState]["background"]->Move(vec2(0,-1));
        }
        if(state[SDL_SCANCODE_LEFT])
        {
            spriteGroups[currentState]["background"]->Move(vec2(-1,0));
        }
        if(state[SDL_SCANCODE_RIGHT])
        {
            spriteGroups[currentState]["background"]->Move(vec2(1,0));
        }
    }
}

void Game::Render()
{
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f); // Ensure alpha is set to 1.0f for solid background
    glClear(GL_COLOR_BUFFER_BIT);

    timeValue = (SDL_GetTicks() / 1000.0f);

    if (spriteGroups.find(currentState) != spriteGroups.end()) 
    {
        for (auto& [key, sprite]: spriteGroups[currentState]) 
        {  
            sprite->Draw();
        }
    }

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
        Update();
        Render();

        // Update the window with OpenGL
        SDL_GL_SwapWindow(mWindow.GetWindow());  
    }
}