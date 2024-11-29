#include "Game.hpp"

Game::Game() : 
    mWindow(Window()),
    mSpriteRenderer(SpriteRenderer())
{
}

void Game::InitMenu()
{
    mMenuChoices = {
        GetSprite(mCurrentGameState, "start-button"),
        GetSprite(mCurrentGameState, "exit-button")
    };

    mMenuChoice = 0;  // Start with the first menu option
}

void Game::ProcessEvents()
{
 SDL_Event& event = mWindow.GetWindowEvent();
    while (SDL_PollEvent(&event))
    {
        if (event.type == SDL_QUIT)
        {
            mWindow.SetWindowClosedBoolean(true);
        }
        else if (event.type == SDL_WINDOWEVENT)
        {
            HandleWindowEvent(event);
        }
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_F11)
            {
                mWindow.ToggleFullscreen();
            }
            
            if (mCurrentGameState == GameState::START_MENU)
            {
                const Uint8* state = SDL_GetKeyboardState(NULL);
                Uint32 currentTime = SDL_GetTicks();

                if (currentTime - mLastSelectionTime >= mSelectionDelay)
                {
                    if (event.key.keysym.sym == SDLK_LEFT)
                    {
                        mMenuChoices[mMenuChoice]->SetColor(vec3(1));
                        mMenuChoice = (mMenuChoice - 1 + mMenuChoices.size()) % mMenuChoices.size();
                        mMenuChoices[mMenuChoice]->SetColor(vec3(1,1,0));
                        mLastSelectionTime = currentTime;
                    }

                    if (event.key.keysym.sym == SDLK_RIGHT)
                    {
                        mMenuChoices[mMenuChoice]->SetColor(vec3(1));  // Stop flash on the previous choice
                        mMenuChoice = (mMenuChoice + 1) % mMenuChoices.size();
                        mMenuChoices[mMenuChoice]->SetColor(vec3(1,1,0));
                        mLastSelectionTime = currentTime;
                    }
                }
            }
        }
    }
}

static Uint32 lastChoiceTime = 0;  // Track the last choice time for delay handling

// Timing constants
const Uint32 selectionDelay = 200; 


void Game::Initialize()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Set up orthgraphic projection matrix
    mat4 orthographicProjection = glm::ortho(0.0f, static_cast<float>(mWindow.GetWindowWidth()),
        static_cast<float>(mWindow.GetWindowHeight()), 0.0f, -1.0f, 1.0f);
    // Set up perspective projection matrix
    mat4 perspectiveProjection = glm::perspective(glm::radians(45.0f), static_cast<float>(mWindow.GetWindowWidth())
        / static_cast<float>(mWindow.GetWindowHeight()), 0.1f, 100.0f);
        
    // load shaders
    ResourceManager::LoadShader("\\shaders\\DefaultVertexShader.glsl", "\\shaders\\DefaultFragmentShader.glsl", "default");
    ResourceManager::GetShader("default").Use().SetMatrix4("projection", orthographicProjection);
    ResourceManager::GetShader("default").Use().SetInteger("image", 0);
    // configure perspective projection 
    ResourceManager::LoadShader("\\shaders\\PerspectiveProjectionVertexShader.glsl","\\shaders\\DefaultFragmentShader.glsl", "default-3D");
    ResourceManager::GetShader("default-3D").Use().SetMatrix4("projection", perspectiveProjection);
    ResourceManager::GetShader("default-3D").Use().SetInteger("image", 0);
    // load textures
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-dots-dots-cropped.png",true,"background-dots");
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-arrows-squares-edit-cropped.png",true,"background");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-logo-2x-new.png", true, "game-logo");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-start-button.png", true, "start-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-exit-button.png", true, "exit-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-user-navigation-assist.png", true, "start-menu-ua"); 

    // Set initial game state to start menu
    mCurrentGameState = GameState::START_MENU;

    mSpriteRenderer.Initialize();

    // Initialize sprites for the START_MENU state

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "background",
        ResourceManager::GetTexture("background"),
        vec2(0, 0),
        glm::vec2(1960.178, 1033.901),
        0.0f,
        vec3(1.0f),
        ResourceManager::GetShader("default"),
        false,
        vec2(0,0),
        2
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "background-dots",
        ResourceManager::GetTexture("background-dots"), 
        vec2(0, 0), 
        vec2(1920, 994.167), 
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "game-logo",
        ResourceManager::GetTexture("game-logo"), 
        vec2(372.256, 193.333), 
        vec2(1162.667, 573.998), 
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "start-button",
        ResourceManager::GetTexture("start-button"), 
        vec2(862.230f, 720.000f), 
        vec2(195.541f, 73.988f), 
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "exit-button",
        ResourceManager::GetTexture("exit-button"), 
        vec2(889.921f, 824.483f), 
        vec2(143.693f, 78.957f), 
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.CreateSprite(
        GameState::START_MENU,
        "start-menu-ua",
        ResourceManager::GetTexture("start-menu-ua"),
        vec2(0, 988.918),
        vec2(1920, 91.082),
        0.0f, 
        vec3(1.0f), 
        ResourceManager::GetShader("default"),
        false
    );

    mSpriteRenderer.LoadDefaultSprites(GameState::START_MENU);

    InitMenu();

    mFirstFrame = true;
}

void Game::CalculateDeltaTime()
{
    Uint32 currentTime = SDL_GetTicks();
    mDeltaTime = (currentTime - mLastFrame) / 1000.0f;
    mLastFrame = currentTime;
}

void Game::Update()
{
    GetSprite(mCurrentGameState, "background")->MoveTextureCoordinate(vec2(0, -0.1f * mDeltaTime));

    if(mCurrentGameState == GameState::START_MENU)
    {
        if(mFirstFrame)
        {
            mMenuChoices[mMenuChoice]->SetColor(vec3(1,1,0));
            mFirstFrame = false;
        }
    }

    UpdateSprites(mCurrentGameState);
}


void Game::Render()
{
    // Clear the screen with a solid background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render all sprites for the current game state
    mSpriteRenderer.DrawSprites(mCurrentGameState);

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
        CalculateDeltaTime();
         // Handle input and window events
        ProcessEvents();
        Update();
        Render();
        // Update the window with OpenGL
        SDL_GL_SwapWindow(mWindow.GetWindow());  
    }
}

void Game::UpdateSprites(GameState gameState)
{
    for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[gameState]) 
    {
        sprite->Update(mDeltaTime);
    }
}
Sprite* Game::GetSprite(GameState gameState, string name)
{
    return mSpriteRenderer.mCurrentlyRenderedSprites[gameState][name];
}

