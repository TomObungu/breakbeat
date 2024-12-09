#include "Game.hpp"

Game::Game() :
    mWindow(Window()),
    mSpriteRenderer(SpriteRenderer())
{
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
        // Check for key inputs
        else if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_F11)
            {
                mWindow.ToggleFullscreen();
            }
            
            HandleMenuInput(event);
        }
    }
}

void Game::Initialize()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // Set up orthgraphic projection matrix
    mat4 orthographicProjection = glm::ortho(
        0.0f, 
        static_cast<float>(mWindow.GetWindowWidth()),
        static_cast<float>(mWindow.GetWindowHeight()), 
        0.0f, 
        -1.0f, 
        1.0f
    );
    
    // Set up perspective projection matrix
    float aspectRatio = static_cast<float>(mWindow.GetWindowWidth()) / static_cast<float>(mWindow.GetWindowHeight());
    mat4 perspectiveProjection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
    CheckGLErrors("After setting the orthographic matrix");
    // load shaders
    ResourceManager::LoadShader("\\shaders\\DefaultVertexShader.glsl", "\\shaders\\DefaultFragmentShader.glsl", "default");
    ResourceManager::GetShader("default").Use().SetMatrix4("projection", orthographicProjection);
    // configure perspective projection
    ResourceManager::LoadShader("\\shaders\\PerspectiveProjectionVertexShader.glsl","\\shaders\\PerspectiveProjectionFragmentShader.glsl", "default-3D");
    ResourceManager::GetShader("default-3D").Use().SetMatrix4("projection", perspectiveProjection);
    CheckGLErrors("After setting the projection matrix");

    ResourceManager::LoadShader("\\shaders\\TextRendererVertexShader.glsl", "\\shaders\\TextRendererFragmentShader.glsl", "text");
    // load textures

    /* START MENU */
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-dots-dots-cropped.png",true,"background-dots");
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-arrows-squares-edit-cropped.png",true,"background");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-logo-2x-new.png", true, "game-logo");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-start-button.png", true, "start-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-exit-button.png", true, "exit-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-user-navigation-assist.png", true, "start-menu-ua");

    /* MAIN_MENU */
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-user-navigation-assist-new.png",true,"main-menu-ua");
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-settings-user-interface.png",true,"main-menu-settings-button");
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-chart-editor-user-interface.png",true,"main-menu-chart-editor-button");
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-chart-selection-user-interface.png",true,"main-menu-chart-selection-button");
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-back-button-user-interface.png",true,"main-menu-back-button");

    for (auto& [key, texture] : ResourceManager::Textures) 
    {
    std::cout << "Texture Name: " << key 
              << ", ID: " << texture.ID 
              << ", Handle: " << texture.handle << std::endl;
    }

    mSpriteRenderer.Initialize();

    mSpriteRenderer.mCurrentlyRenderedSprites.clear();

    // Initialize sprites
    InitializeSprites();

    // Initialize menus;
    InitializeMenus();

    mSpriteRenderer.LoadDefaultSprites(GameState::START_MENU);

    Text = new TextRenderer(mWindow.GetWindowHeight(), mWindow.GetWindowWidth());
    Text->Load("C:/Users/deeza/OneDrive/breakbeat/fonts/OpenSans-ExtraBold.ttf",24);
 
    mFirstFrame = true;
    mTransitioningDark = false;
    mAllDark = false;
}

void Game::CalculateDeltaTime()
{
    Uint64 currentTime = SDL_GetTicks();
    mDeltaTime = (currentTime - mLastFrame);
    mLastFrame = currentTime;
}

void Game::Update()
{
    GetSprite(mCurrentGameState, "background")->MoveTextureCoordinate(vec2(0, -0.1 / (1000 / mDeltaTime)));

    if(mCurrentGameState == GameState::START_MENU)
    {
        if(mFirstFrame)
        {
            GetMenu(mCurrentGameState, "start-menu")->GetCurrentMenuOption()->SetColor(vec3(1,1,0));
            GetMenu(mCurrentGameState, "start-menu")->GetCurrentMenuOption()->SetRotation(true,vec3(0,1,0),1,360);
               
            mFirstFrame = false;
        }
    }

    if(mCurrentGameState == GameState::MAIN_MENU)
    {
        if(mFirstFrame)
        {
            GetMenu(mCurrentGameState, "main-menu")->GetCurrentMenuOption()->SetRotation(true,vec3(0,0,1),0.2,10);
            GetMenu(mCurrentGameState, "main-menu")->GetCurrentMenuOption()->SetScale(true,1.05,0.2);
            mFirstFrame = false;
        }
    }

    CheckForTransitionState();

    UpdateSprites(mCurrentGameState);
}

void Game::Render()
{
    // Clear the screen with a solid background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render all sprites for the current game state
    mSpriteRenderer.DrawSprites(mCurrentGameState);
    glFinish();
    CheckGLErrors("After drawing a sprite!");
    
    Text->RenderText(std::to_string(SDL_GetTicks()),480.0f,540.0f,2.0f,vec3(1,1,1));
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
        CheckGLErrors("After updating a sprite");
    }
    
}

void Game::Transition(GameState newGameState)
{

    // If it is the first frame and the sprites are not being darkened 
    // enable the darken animation for all sprites in current game state 
    
    if(!mTransitioningDark && mFirstTransitionFrame)
    {
        std::cout << "Darkening sprites!\n";
        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            sprite->SetDarken(true);
        }
        mTransitioningDark = true;
        mFirstTransitionFrame = false;
    }

    // If the sprites are in their darkening state, check if all the sprites are fully dark.
    //  If they are not break out of the recursive function using return

    if(mTransitioningDark && !mAllDark)
    {
        std::cout << "Checking if sprites are darkened!\n";
        mAllDark = true;

        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            if(sprite->GetDarkenState() != true)
                mAllDark = false;
            return;
        }
    }

    // Once all the sprites are dark then load the new sprites 
    //then set the darkening Boolean to false and set the brightening Boolean to true

    if(mAllDark)
    {
        std::cout << "Loading new sprites!\n";
        mTransitioningDark = false;
        mTransitioningLight = true;
        LoadDefaultSprites(newGameState);
        mCurrentGameState = newGameState;
        std::cout << "Loading new sprites and setting them to color 0!\n";
        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            sprite->SetColor(vec3(0));
        }
        mAllLight = false;
        std::cout << "Brightening new sprites!\n";
        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            sprite->SetBrighten(true);
        }
        mAllDark = false;
    }

    if(mTransitioningLight && !mAllLight)
    {
        std::cout << "Checking if new sprites are brightened!\n";
        mAllLight = true;

        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            if(sprite->GetBrightenState() != true)
                mAllLight = false;
            return;
        }
    }

    if(mAllLight)
    {
        std::cout << "Finished transition!\n";
        mAllDark = false;
        mAllLight = true;
        mTransitioningDark = false;
        mTransitioningLight = false;
        mTransitioningGameState = GameState::NOT_TRANSITIONING;
        mHasTransitioned = true;
        mFirstTransitionFrame = true;
        mFirstFrame = true;
    }
}

void Game::CheckForTransitionState()
{
    if(!mHasTransitioned && (mTransitioningGameState != GameState::NOT_TRANSITIONING))
    {
        Transition(mTransitioningGameState);
    }
}

void Game::TransitionToGameState(GameState newGameState)
{
    mTransitioningGameState = newGameState;
    mHasTransitioned = false;
}

// Function to get the string representation of an OpenGL error
string Game::GetGLErrorString(GLenum error)
{
    switch (error)
    {
        case GL_NO_ERROR:
            return "No error";
        case GL_INVALID_ENUM:
            return "GL_INVALID_ENUM: An unacceptable value is specified for an enumerated argument.";
        case GL_INVALID_VALUE:
            return "GL_INVALID_VALUE: A numeric argument is out of range.";
        case GL_INVALID_OPERATION:
            return "GL_INVALID_OPERATION: The specified operation is not allowed in the current state.";
        case GL_OUT_OF_MEMORY:
            return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the command.";
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not complete.";
        default:
            return "Unknown error code";
    }
}

// Function to check for OpenGL errors and print them
void Game::CheckGLErrors(const string& context)
{
    GLenum error;
    while ((error = glGetError()) != GL_NO_ERROR)
    {
        std::cerr << "[OpenGL Error] (" << error << "): " << GetGLErrorString(error);
        if (!context.empty())
        {
            std::cerr << " | Context: " << context;
        }
        std::cerr << std::endl;
    }
}