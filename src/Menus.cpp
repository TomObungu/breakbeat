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

    Menu* startMenu = GetMenu(GameState::START_MENU, "start-menu");
    Menu* mainMenu = GetMenu(GameState::MAIN_MENU, "main-menu");

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
        mainMenu->GetCurrentMenuOption()->SetRotation(true,vec3(0,0,1),0.1,5);
        mainMenu->GetCurrentMenuOption()->SetScale(true,1.05,0.2);
    });

    mainMenu->SetSelectionAnimation(
        [this,mainMenu](){
        mainMenu->GetCurrentMenuOption()->SetRotation(true,vec3(0,1,0),0.5,360);
    });

    mainMenu->SetUnhighlightAnimation(
        [this,mainMenu](){
        mainMenu->GetCurrentMenuOption()->SetRotation(true,vec3(0,0,1),0.05,0);
        mainMenu->GetCurrentMenuOption()->SetScale(true,1.0,0.1);
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

                if (startMenu->GetCurrentMenuOption() == GetSprite(mCurrentGameState, "exit-button"))
                {
                    mWindow.SetWindowClosedBoolean(true);
                }
                // If the current menu option is the exit button sprite then close the application
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
            }
        }
    }
}

void Game::CreateMenu(GameState gamestate, vector<Sprite*> sprites,bool wrapAround, string name)
{
    Menu* menu = new Menu(sprites,wrapAround);
    mCurrentMenus[gamestate][name] = menu;
}

Menu* Game::GetMenu(GameState gamestate,string name)
{
    return mCurrentMenus[gamestate][name];
}
