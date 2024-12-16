#include "Game.hpp"

void Game::HandleMouseInput(SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        // Update mouse position based on the event
        mMouse->Update(event);

        // Check for colliding sprite in the current game state
        Sprite* collidingSprite = CheckCollidingSprite(mCurrentGameState);

        if (collidingSprite)
        {
            // Handle collisions based on the current game state
            Menu* currentMenu = nullptr;

            if (mCurrentGameState == GameState::START_MENU)
            {
                currentMenu = GetMenu(GameState::START_MENU, "start-menu");

                if (collidingSprite == GetSprite(GameState::START_MENU, "start-button"))
                {
                    currentMenu->PlayUnhighlightAnimation();
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlayHighlightAnimation();
                }
                else if (collidingSprite == GetSprite(GameState::START_MENU, "exit-button"))
                {
                    currentMenu->PlayUnhighlightAnimation();
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlayHighlightAnimation();
                }
            }
            else if (mCurrentGameState == GameState::MAIN_MENU)
            {
                currentMenu = GetMenu(GameState::MAIN_MENU, "main-menu");

                if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-back-button"))
                {
                    currentMenu->PlayUnhighlightAnimation();
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlayHighlightAnimation();
                }
                else if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-chart-editor-button"))
                {
                    currentMenu->PlayUnhighlightAnimation();
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlayHighlightAnimation();
                }
                else if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-chart-selection-button"))
                {
                    currentMenu->PlayUnhighlightAnimation();
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlayHighlightAnimation();
                }
                else if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-settings-button"))
                {
                    currentMenu->PlayUnhighlightAnimation();
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlayHighlightAnimation();
                }
            }
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        Sprite* collidingSprite = CheckCollidingSprite(mCurrentGameState);

        if (collidingSprite)
        {
            Menu* currentMenu = nullptr;

            if (mCurrentGameState == GameState::START_MENU)
            {
                currentMenu = GetMenu(GameState::START_MENU, "start-menu");

                if (collidingSprite == GetSprite(GameState::START_MENU, "start-button"))
                {
                    TransitionToGameState(GameState::MAIN_MENU);
                }
                else if (collidingSprite == GetSprite(GameState::START_MENU, "exit-button"))
                {
                    mWindow.SetWindowClosedBoolean(true);
                }
            }
            else if( mCurrentGameState == GameState::MAIN_MENU)
            {

                currentMenu = GetMenu(GameState::MAIN_MENU, "main-menu");

                if (collidingSprite == GetSprite(mCurrentGameState, "main-menu-settings-button"))
                {
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlaySelectionAnimation();
                    if(currentMenu->GetCurrentMenuOption()->IsAnimationComplete())
                        TransitionToGameState(GameState::SETTINGS);
                }
                if (collidingSprite == GetSprite(mCurrentGameState, "main-menu-back-button"))
                {
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlaySelectionAnimation();
                    TransitionToGameState(GameState::START_MENU);
                }
            }
        }
    }
}
