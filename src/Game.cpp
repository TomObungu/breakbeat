#include "Game.hpp"
#include <format>

Game::Game() :
    mWindow(Window()),
    mSpriteRenderer(SpriteRenderer()),
    mTextRenderer(TextRenderer())
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
        if (event.type == SDL_KEYDOWN)
        {
            if (event.key.keysym.sym == SDLK_F11)
            {
                mWindow.ToggleFullscreen();
            }
            
            HandleMenuInput(event);
            HandleKeyboardInput(event);
            if (mCurrentGameState == GameState::CHART_EDITOR_SELECTION_MENU)
            {
                HandleChartScrolling(event);
                HandleDifficultyScrolling(event);

                if (!mNewChartSpritesOnScreen && event.key.keysym.sym == SDLK_ESCAPE)
                {
                    TransitionToGameState(GameState::MAIN_MENU);
                    mSoundEngine->stopAllSounds();
                }
            }  
            if (mCurrentGameState == GameState::CHART_SELECTION_MENU)
            {
                HandleChartScrolling(event);
                HandleDifficultyScrolling(event);

                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    TransitionToGameState(GameState::MAIN_MENU);
                    mSoundEngine->stopAllSounds();
                }
            }  
            if (mCurrentGameState == GameState::MAIN_GAMEPLAY)
            {
                if (mSongPlaying)
                {
                    HandleHitRegistration(event);
                }

                // Handle exiting gameplay when Escape is pressed
                if (event.key.keysym.sym == SDLK_ESCAPE)
                {
                    mSoundEngine->stopAllSounds(); // Stop any playing sounds
                    // Transition back to Chart Selection
                    TransitionToGameState(GameState::CHART_SELECTION_MENU);
                }
            }
        }
        if (event.type == SDL_KEYUP)
        {
            if (mCurrentGameState == GameState::MAIN_GAMEPLAY)
            {
                if(mSongPlaying)
                    HandleHitRelease(event);
            }
        }
        if (event.type == SDL_MOUSEMOTION)
        {
            mMouse->Update(event);
        }
        if(mHasTransitioned)
            HandleMouseInput(event);
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
    // load shaders
    ResourceManager::LoadShader("\\shaders\\DefaultVertexShader.glsl", "\\shaders\\DefaultFragmentShader.glsl", "default");
    ResourceManager::GetShader("default").Use().SetMatrix4("projection", orthographicProjection);
    ResourceManager::LoadShader("\\shaders\\MouseVertexShader.glsl", "\\shaders\\DefaultFragmentShader.glsl", "cursor");
    ResourceManager::GetShader("cursor").Use().SetMatrix4("projection", orthographicProjection);
    // configure perspective projection
    ResourceManager::LoadShader("\\shaders\\PerspectiveProjectionVertexShader.glsl","\\shaders\\PerspectiveProjectionFragmentShader.glsl", "default-3D");
    ResourceManager::GetShader("default-3D").Use().SetMatrix4("projection", perspectiveProjection);
    ResourceManager::LoadShader("\\shaders\\TextRendererVertexShader.glsl", "\\shaders\\TextRendererFragmentShader.glsl", "text");
    ResourceManager::GetShader("text").Use().SetMatrix4("projection", orthographicProjection);
    
    InitializeTextures();


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

    mSpriteRenderer.LoadDefaultSprites(mCurrentGameState);

    mTextRenderer.Initialize();

    mTextRenderer.mCurrentlyRenderedTexts.clear();

    InitializeFonts();

    InitializeTexts();

    mTextRenderer.LoadTexts(mCurrentGameState);

    // Initialize menus;
    InitializeMenus();

    mMouse = new Mouse();
    mMouse->InitializeMouse();

    mSoundEngine = createIrrKlangDevice();

    UpdateSettings();

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

    CheckForTransitionState();

    UpdateSprites(mCurrentGameState);

    UpdateTexts(mCurrentGameState);

    if(GetSprite(mCurrentGameState, "background")!=nullptr)
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
            //GetMenu(mCurrentGameState, "main-menu")->GetCurrentMenuOption()->SetRotation(true,vec3(0,0,1),0.2,10);
            //GetMenu(mCurrentGameState, "main-menu")->GetCurrentMenuOption()->SetScale(true,1.05,0.2);
            //GetMenu(mCurrentGameState, "main-menu")->GetCurrentMenuOption()->SetColor(vec3(1.0f,1.0f,0.0f));
            mFirstFrame = false;
        }
    }
    if(mCurrentGameState == GameState::SETTINGS)
    {
        if(mFirstFrame)
        {
            GetMenu(mCurrentGameState, "settings-menu")->SetCurrentTextMenuOption(
                GetText(GameState::SETTINGS,"scroll-speed-text"));
            GetMenu(mCurrentGameState, "settings-menu")->PlayHighlightAnimation();
            mFirstFrame = false;
        }
    }
    if(mCurrentGameState == GameState::CHART_EDITOR_SELECTION_MENU)
    {
        
        CheckNewChartButton();

        if(mFirstFrame)
        {
            InitializeChartSelection();
            mFirstFrame = false;
            removingSprites = true;
        }
            
    }
    
    if(mCurrentGameState == GameState::CHART_SELECTION_MENU)
    {
        
        if(mFirstFrame)
        {
            InitializeChartSelection();
            mFirstFrame = false;
            removingSprites = true;
        }
            
    }

    if (mCurrentGameState == GameState::MAIN_GAMEPLAY)
    {
        if(!mGameActive)
        {
            if (mWaitingForGameplayStart)
            {
                // Wait for a short delay before initializing gameplay
                if (SDL_GetTicks() - mGameplayStartTime >= mGameplayDelay)
                {
                    InitializeMainGameplay();
                    mWaitingForGameplayStart = false; // Now ready to start gameplay
                }
            }
        mGameActive = true;
        }
        else
        {
            HandleMainGameplay();
        }
    }

    if (mCurrentGameState == GameState::CHART_EDITOR)
    {
        if (mFirstFrame)
        {
            InitializeChartEditor();
            mFirstFrame = false;
        }

        HandleChartEditor();
    }

}

void Game::Render()
{
    // Clear the screen with a solid background color
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Render all sprites for the current game state
    mSpriteRenderer.DrawSprites(mCurrentGameState);
    mTextRenderer.DrawTexts(mCurrentGameState);
    mMouse->DrawMouse();

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
        if(sprite != nullptr)
            sprite->Update(mDeltaTime);
    }     
    for (auto& [key, sprite] : mSpriteRenderer.mNoteBuffer[gameState])
    {
        if(sprite != nullptr)
            sprite->Update(mDeltaTime);
    } 
}

void Game::UpdateTexts(GameState gameState)
{
    for (auto& [key, text] : mTextRenderer.mCurrentlyRenderedTexts[gameState])
    {
        if(text != nullptr)
        {
            text->Update(mDeltaTime);
        }
    } 
}

void Game::Transition(GameState newGameState)
{
    // If it is the first frame and the sprites are not being darkened 
    // enable the darken animation for all sprites in current game state 
    
    if(!mTransitioningDark && mFirstTransitionFrame)
    {
        // std::cout << "Darkening sprites!\n";
        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            if(sprite!=nullptr)
                sprite->SetDarken(true);
        }
        for (auto& [key, text] : mTextRenderer.mCurrentlyRenderedTexts[mCurrentGameState])
        {
            text->SetDarken(true);
        }        
        mTransitioningDark = true;
        mFirstTransitionFrame = false;
    }

    // If the sprites are in their darkening state, check if all the sprites are fully dark.
    //  If they are not break out of the recursive function using return

    if(mTransitioningDark && !mAllDark)
    {
        // std::cout << "Checking if sprites are darkened!\n";
        mAllDark = true;

        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            if (sprite != nullptr)
            {
                if (sprite->GetDarkenState() != true)
                {
                    mAllDark = false;
                    return;
                }
            }
        }
    }

    // Once all the sprites are dark then load the new sprites 
    //then set the darkening Boolean to false and set the brightening Boolean to true

    if(mAllDark)
    {
        // std::cout << "Loading new sprites!\n";
        mTransitioningDark = false;
        mTransitioningLight = true;
        mCurrentGameState = newGameState;
        mSpriteRenderer.mNoteBuffer[mCurrentGameState].clear();
        LoadDefaultSprites(newGameState);
        mTextRenderer.LoadTexts(newGameState);
        mFirstFrame = true;
        // std::cout << "Loading new sprites and setting them to color 0!\n";
        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            sprite->SetColor(vec3(0));
        }
        for (auto& [key, text] : mTextRenderer.mCurrentlyRenderedTexts[mCurrentGameState])
        {
            text->SetColor(vec3(0));
        }
        mAllLight = false;
        // std::cout << "Brightening new sprites!\n";
        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            sprite->SetBrighten(true);
        }
        for (auto& [key, text] : mTextRenderer.mCurrentlyRenderedTexts[mCurrentGameState])
        {
            text->SetBrighten(true);
        }
        mAllDark = false;
    }

    if(mTransitioningLight && !mAllLight)
    {
        // std::cout << "Checking if new sprites are brightened!\n";
        mAllLight = true;

        for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
        {
            if (sprite != nullptr)
            {
                if (sprite->GetBrightenState() != true)
                {
                    mAllLight = false;
                    return;
                }
            }
        }
    }

    if(mAllLight)
    {
        // std::cout << "Finished transition!\n";
        mAllDark = false;
        mTransitioningDark = false;
        mTransitioningLight = false;
        mTransitioningGameState = GameState::NOT_TRANSITIONING;
        mHasTransitioned = true;
        mFirstTransitionFrame = true;
        if (mCurrentGameState == GameState::CHART_SELECTION_MENU)
        {
            mGameActive = false;
            mSongPlaying = false;
            
            firstColumn = {
             0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
             "main-gameplay-left-note",
             581.936, 0,
             {},
             {},
             {},
             {}, {}, {}, false, false, false, 0, 0 };
            secondColumn = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            "main-gameplay-down-note",
            765.423, 0,
            {},
            {},
            {},
            {}, {}, {}, false, false, false, 0, 0 };
            thirdColumn = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            "main-gameplay-up-note",
            949.361, 0,
            {},
            {},
            {},
            {}, {}, {},false, false, false, 0, 0 };
            fourthColumn = {
            0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            "main-gameplay-right-note",
            1138.061, 0,
            {},
            {},
            {},
            {}, {}, {},false, false, false, 0, 0 };

            // Clear note columns
            for (auto& noteColumn : mNoteColumns)
            {
                noteColumn = {};
            }

            mSongStartTime = 0;
            mTimeElapsed = 0;
            mDelayStartTime = 0;
            mNegativeOffset = 0;
            mTimeTakenToFall = 0;

            mAccuracy = 0;
            mScore = 0;
            mMaximumPossibleScore = 0;
            mHealth = 100;

            mFlawlessCount = 0;
            mPerfectCount = 0;
            mGreatCount = 0;
            mGoodCount = 0;
            mBadCount = 0;
            mMissCount = 0;

            mWaitingForGameplayStart = true;
            mGameplayStartTime = SDL_GetTicks();
        }
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