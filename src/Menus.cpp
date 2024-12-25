#include "Game.hpp"

void Game::InitializeMenus()
{

    // Create menu system for start menu
    CreateMenu(GameState::START_MENU,
        vector<Sprite*> 
        {
            GetDefaultSprite(GameState::START_MENU, "start-button"),
            GetDefaultSprite(GameState::START_MENU, "exit-button"), 
        }, 
        true,
        "start-menu"
    );

    CreateMenu(GameState::MAIN_MENU,
        vector<Sprite*> 
        {
            GetDefaultSprite(GameState::MAIN_MENU,"main-menu-chart-selection-button"),
            GetDefaultSprite(GameState::MAIN_MENU,"main-menu-chart-editor-button"),
            GetDefaultSprite(GameState::MAIN_MENU,"main-menu-settings-button"),
            GetDefaultSprite(GameState::MAIN_MENU,"main-menu-back-button")
        }, 
        true,
        "main-menu"
    );

    CreateMenu(GameState::SETTINGS,
        vector<Text*> 
        {
            GetDefaultText(GameState::SETTINGS, "scroll-speed-text"),
            GetDefaultText(GameState::SETTINGS, "receptor-size-text"),
            GetDefaultText(GameState::SETTINGS, "scroll-direction-text"),
            GetDefaultText(GameState::SETTINGS, "left-keybind-text"),
            GetDefaultText(GameState::SETTINGS, "down-keybind-text"),
            GetDefaultText(GameState::SETTINGS, "up-keybind-text"),
            GetDefaultText(GameState::SETTINGS, "right-keybind-text"), 
        }, 
        true,
        "settings-menu"
    );

    Menu* startMenu = GetMenu(GameState::START_MENU, "start-menu");
    Menu* mainMenu = GetMenu(GameState::MAIN_MENU, "main-menu");
    Menu* settingsMenu = GetMenu(GameState::SETTINGS, "settings-menu");

    startMenu->SetHighlightAnimation(
        [this,startMenu](){
        startMenu->GetCurrentMenuOption()->SetColor(vec3(1.0f, 1.0f, 0.0f));
    });

    startMenu->SetUnhighlightAnimation(
        [this,startMenu](){
        startMenu->GetCurrentMenuOption()->SetColor(vec3(1.0f));  
    });

    mainMenu->SetHighlightAnimation(
        [this,mainMenu](){
        mainMenu->GetCurrentMenuOption()->SetRotation(true,vec3(0,0,1),0.1,5); // Rotate the sprite when its being highlighted
        mainMenu->GetCurrentMenuOption()->SetScale(true,1.05,0.2);
        mainMenu->GetCurrentMenuOption()->SetColor(vec3(1.0f,1.0f,0.0f)); // Highlight the sprite
    });

    mainMenu->SetSelectionAnimation(
        [this,mainMenu](){
        mainMenu->GetCurrentMenuOption()->SetRotation(true,vec3(0.0f,1.0f,0),0.5,360); // Play a spinning animation when enter is pressed
    });

    mainMenu->SetUnhighlightAnimation(
        [this,mainMenu](){
        mainMenu->GetCurrentMenuOption()->SetRotation(true,vec3(0,0,1),0.05,0);
        mainMenu->GetCurrentMenuOption()->SetScale(true,1.0,0.1);
        mainMenu->GetCurrentMenuOption()->SetColor(vec3(1.0f));  
    });

    settingsMenu->SetHighlightAnimation(
        [this,settingsMenu](){
        settingsMenu->GetCurrentTextOption()->SetScale(true, 1.25,0.05);
    });

    settingsMenu->SetSelectionAnimation(
        [this,settingsMenu](){
        settingsMenu->GetCurrentTextOption()->SetColor(vec3(1.0f,1.0f,0.0f));
    });

    settingsMenu->SetUnselectionAnimation(
        [this,settingsMenu](){
        settingsMenu->GetCurrentTextOption()->SetColor(vec3(1.0f,1.0f,1.0f));
    });

    settingsMenu->SetUnhighlightAnimation(
        [this,settingsMenu](){
        settingsMenu->GetCurrentTextOption()->SetScale(true,1.0,0.1);
        settingsMenu->GetCurrentTextOption()->SetColor(vec3(1.0f));
    });
    
}

void Game::HandleMenuInput(SDL_Event& event)
{
    // If the current game state is start menu then check for input
    if (mCurrentGameState == GameState::START_MENU)
    {
        // Store a pointer to the start menu object
        Menu* startMenu = GetMenu(mCurrentGameState, "start-menu");

        // Update the value of the current time at this moment
        startMenu->UpdateCurrentTime();

        // If the time elapsed between the last update is greater than 200ms
        if (startMenu->CheckSelectionTime())
        {
            // IF the key pressed is the left key
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                startMenu->PlayUnhighlightAnimation();
                // Update menu choice index with wrap-around
                startMenu->IncrementMenuChoice();
                startMenu->PlayHighlightAnimation();
                startMenu->UpdateLastSelectedTime();
            }   
            // If the key pressed is the right key
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                startMenu->PlayUnhighlightAnimation();
                // Update menu choice index with wrap-around
                startMenu->DecrementMenuChoice();
                startMenu->PlayHighlightAnimation();
                startMenu->UpdateLastSelectedTime();
            }
            // If they pressed in the return key
            if (event.key.keysym.sym == SDLK_RETURN)
            {   
                // If the currrent menu option is the start button sprite then call the transition animation
                if (startMenu->GetCurrentMenuOption() == GetSprite(mCurrentGameState, "start-button"))
                {
                    TransitionToGameState(GameState::MAIN_MENU);
                }
                // If the current menu option is the exit button sprite then close the application
                if (startMenu->GetCurrentMenuOption() == GetSprite(mCurrentGameState, "exit-button"))
                {
                    mWindow.SetWindowClosedBoolean(true);
                }
            }
        }
    }
    else if(mCurrentGameState == GameState::MAIN_MENU)
    {
        Menu* mainMenu = GetMenu(mCurrentGameState, "main-menu");

        mainMenu->UpdateCurrentTime();

        // If the time elapsed between the last update is greater than 200ms
        if (mainMenu->CheckSelectionTime())
        {
            if (event.key.keysym.sym == SDLK_LEFT)
            {
                mainMenu->PlayUnhighlightAnimation();
                // Update menu choice index with wrap-around
                mainMenu->DecrementMenuChoice();
                mainMenu->PlayHighlightAnimation();
                mainMenu->UpdateLastSelectedTime();
            }   
            // If the key pressed is the right key
            if (event.key.keysym.sym == SDLK_RIGHT)
            {
                mainMenu->PlayUnhighlightAnimation();
                // Update menu choice index with wrap-around
                mainMenu->IncrementMenuChoice();
                mainMenu->PlayHighlightAnimation();
                mainMenu->UpdateLastSelectedTime();
            }
            if (event.key.keysym.sym == SDLK_DOWN)
            {
                mainMenu->PlayUnhighlightAnimation();
                // Update menu choice index with wrap-around
                mainMenu->MoveMenuChoiceDown();
                mainMenu->PlayHighlightAnimation();
                mainMenu->UpdateLastSelectedTime();
            }
            if (event.key.keysym.sym == SDLK_UP)
            {
                mainMenu->PlayUnhighlightAnimation();
                // Update menu choice index with wrap-around
                mainMenu->MoveMenuChoiceUp();
                mainMenu->PlayHighlightAnimation();
                mainMenu->UpdateLastSelectedTime();
            }
            // If they pressed in the return key
            if (event.key.keysym.sym == SDLK_RETURN)
            {   
                // If the currrent menu option is settings button call the transition animation
                if (mainMenu->GetCurrentMenuOption() == GetSprite(mCurrentGameState, "main-menu-settings-button"))
                {
                    mainMenu->PlaySelectionAnimation();
                    if(mainMenu->GetCurrentMenuOption()->IsAnimationComplete())
                        TransitionToGameState(GameState::SETTINGS);
                }
                if (mainMenu->GetCurrentMenuOption() == GetSprite(mCurrentGameState, "main-menu-back-button"))
                {
                    mainMenu->PlaySelectionAnimation();
                    TransitionToGameState(GameState::START_MENU);
                }
                if (mainMenu->GetCurrentMenuOption() == GetSprite(mCurrentGameState, "main-menu-chart-editor-button"))
                {
                    mainMenu->PlaySelectionAnimation();
                    TransitionToGameState(GameState::CHART_EDITOR_SELECTION_MENU);
                }
            }
        }
    }
    else if (mCurrentGameState == GameState::SETTINGS)
    {
        Menu* settingsMenu = GetMenu(mCurrentGameState, "settings-menu");

        settingsMenu->UpdateCurrentTime();

        if(settingsMenu->CheckSelectionTime())
        {
            // Navigation between settings options
            if (event.key.keysym.sym == SDLK_UP && !mSelectedSetting)
            {
                settingsMenu->PlayUnhighlightAnimation();
                settingsMenu->DecrementTextMenuChoice();
                settingsMenu->PlayHighlightAnimation();
                settingsMenu->UpdateLastSelectedTime();
            }
            else if (event.key.keysym.sym == SDLK_DOWN && !mSelectedSetting)
            {
                settingsMenu->PlayUnhighlightAnimation();
                settingsMenu->IncrementTextMenuChoice();
                settingsMenu->PlayHighlightAnimation();
                settingsMenu->UpdateLastSelectedTime();
            }
            else if (event.key.keysym.sym == SDLK_RETURN)
            {
                if (!mSelectedSetting)
                {
                    settingsMenu->PlaySelectionAnimation();
                    mSelectedSetting = true;
                }
                else if (mKeybindMode)
                {
                    // Re-enter into keybind mode only after exiting
                    mKeybindMode = false;
                    settingsMenu->GetCurrentMenuOption()->SetColor(vec3(1.0f));
                }
            }
            else if (event.key.keysym.sym == SDLK_ESCAPE)
            {
                if (mSelectedSetting)
                {
                    settingsMenu->PlayUnselectionAnimation();
                    mSelectedSetting = false;
                }
                else
                {
                    TransitionToGameState(GameState::MAIN_MENU);
                }
            }
        }
        if (mSelectedSetting)
        {
            Text* currentText = settingsMenu->GetCurrentTextOption();

            if (currentText == GetText(mCurrentGameState, "scroll-speed-text"))
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    mScrollSpeed++;
                    currentText->UpdateText(std::to_string(mScrollSpeed));
                    UpdateSettings();
                }
                else if (event.key.keysym.sym == SDLK_LEFT)
                {
                    mScrollSpeed--;
                    currentText->UpdateText(std::to_string(mScrollSpeed));
                    UpdateSettings();
                }
            }
            else if (currentText == GetText(mCurrentGameState, "receptor-size-text"))
            {
                if (event.key.keysym.sym == SDLK_RIGHT)
                {
                    mReceptorSize++;
                    currentText->UpdateText(std::to_string(mReceptorSize) + "%");
                    UpdateSettings();
                }
                else if (event.key.keysym.sym == SDLK_LEFT)
                {
                    mReceptorSize--;
                    currentText->UpdateText(std::to_string(mReceptorSize) + "%");
                    UpdateSettings();
                }
            }
            else if(currentText == GetText(mCurrentGameState, "scroll-direction-text"))
            {
                if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_LEFT)
                {
                    if (currentText->GetText() == "Down")
                    {
                        currentText->UpdateText("Up");
                        mScrollDirection = "Up";
                        UpdateSettings();
                    }
                    else if (currentText->GetText() == "Up")
                    {
                        currentText->UpdateText("Down");
                        mScrollDirection = "Down";
                        UpdateSettings();
                    }
                }
            }
            else if (
                currentText == GetText(mCurrentGameState, "left-keybind-text") ||
                currentText == GetText(mCurrentGameState, "down-keybind-text") ||
                currentText == GetText(mCurrentGameState, "up-keybind-text") ||
                currentText == GetText(mCurrentGameState, "right-keybind-text"))
            {
                currentText->SetColor(vec3(1.0f,1.0f,0.0f));
                if (event.type == SDL_KEYDOWN) // Wait for the next key press
                {
                    const char* keyName = SDL_GetKeyName(event.key.keysym.sym);
                    if (keyName && strlen(keyName) > 0) // Check if the key name is valid
                    {
                        std::string newKeybind = keyName;

                        if (currentText == GetText(mCurrentGameState, "left-keybind-text"))
                            mLeftKeybind = newKeybind;
                        else if (currentText == GetText(mCurrentGameState, "down-keybind-text"))
                            mDownKeybind = newKeybind;
                        else if (currentText == GetText(mCurrentGameState, "up-keybind-text"))
                            mUpKeybind = newKeybind;
                        else if (currentText == GetText(mCurrentGameState, "right-keybind-text"))
                            mRightKeybind = newKeybind;

                        // Update the text and settings file
                        currentText->UpdateText(newKeybind);
                        UpdateSettings();

                        // Exit selection mode
                        settingsMenu->GetCurrentTextOption()->SetColor(vec3(1.0f));
                        mSelectedSetting = false;
                    }
                }
            }
        }
    }
}

void Game::CreateMenu(GameState gamestate, vector<Sprite*> sprites,bool wrapAround, string name)
{
    Menu* menu = new Menu(sprites,wrapAround);
    mCurrentMenus[gamestate][name] = menu;
}

void Game::CreateMenu(GameState gamestate, vector<Text*> texts,bool wrapAround, string name)
{
    Menu* menu = new Menu(texts, wrapAround);
    mCurrentMenus[gamestate][name] = menu;
}

Menu* Game::GetMenu(GameState gamestate,string name)
{
    return mCurrentMenus[gamestate][name];
}
