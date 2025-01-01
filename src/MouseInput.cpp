#include "Game.hpp"

void Game::HandleMouseInput(SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        // Update mouse position based on the event
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
                    if(currentMenu->GetCurrentMenuOption() != GetSprite(GameState::MAIN_MENU, "main-menu-back-button"))
                    {
                        currentMenu->PlayUnhighlightAnimation();
                        currentMenu->SetCurrentMenuOption(collidingSprite);
                        currentMenu->PlayHighlightAnimation();
                    }
                }
                else if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-chart-editor-button"))
                {
                    if(currentMenu->GetCurrentMenuOption() != GetSprite(GameState::MAIN_MENU, "main-menu-chart-editor-button"))
                    {
                        currentMenu->PlayUnhighlightAnimation();
                        currentMenu->SetCurrentMenuOption(collidingSprite);
                        currentMenu->PlayHighlightAnimation();
                    }
                }
                else if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-chart-selection-button"))
                {
                    if(currentMenu->GetCurrentMenuOption() != GetSprite(GameState::MAIN_MENU, "main-menu-chart-selection-button"))
                    {
                        currentMenu->PlayUnhighlightAnimation();
                        currentMenu->SetCurrentMenuOption(collidingSprite);
                        currentMenu->PlayHighlightAnimation();
                    }
                }
                else if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-settings-button"))
                {
                    if(currentMenu->GetCurrentMenuOption() != GetSprite(GameState::MAIN_MENU, "main-menu-settings-button"))
                    {
                        currentMenu->PlayUnhighlightAnimation();
                        currentMenu->SetCurrentMenuOption(collidingSprite);
                        currentMenu->PlayHighlightAnimation();
                    }
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
            else if( mCurrentGameState == GameState::SETTINGS)
            {
                Menu* settingsMenu = GetMenu(mCurrentGameState, "settings-menu");
                
                if (mSelectedSetting)
                {
                    Text* currentText = settingsMenu->GetCurrentTextOption();

                    if (currentText == GetText(mCurrentGameState, "scroll-speed-text"))
                    {
                        if (collidingSprite == GetSprite(mCurrentGameState, "settings-increment-right-1"))
                        {
                            mScrollSpeed++;
                            currentText->UpdateText(std::to_string(mScrollSpeed));
                            UpdateSettings();
                        }
                        else if (collidingSprite == GetSprite(mCurrentGameState, "settings-increment-left-1"))
                        {
                            mScrollSpeed--;
                            currentText->UpdateText(std::to_string(mScrollSpeed));
                            UpdateSettings();
                        }
                    }
                    else if (currentText == GetText(mCurrentGameState, "receptor-size-text"))
                    {
                        if (collidingSprite == GetSprite(mCurrentGameState, "settings-increment-right-2"))
                        {
                            mReceptorSize++;
                            currentText->UpdateText(std::to_string(mReceptorSize) + "%");
                            UpdateSettings();
                        }
                        else if (collidingSprite == GetSprite(mCurrentGameState,"settings-increment-left-2"))
                        {
                            mReceptorSize--;
                            currentText->UpdateText(std::to_string(mReceptorSize) + "%");
                            UpdateSettings();
                        }
                    }
                    else if(currentText == GetText(mCurrentGameState, "scroll-direction-text"))
                    {
                        if (collidingSprite == GetSprite(mCurrentGameState, "settings-increment-right-3") || 
                        collidingSprite == GetSprite(mCurrentGameState,"settings-increment-left-3"))
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
                }
            }
            else if (mCurrentGameState == GameState::CHART_EDITOR_SELECTION_MENU)
            {
                if(collidingSprite == GetSprite(mCurrentGameState, "chart-editor-new-chart-button") 
                    && !mShowNewChartScreen)
                {
                    mShowNewChartScreen = true;
                }
                else if(mNewChartSpritesOnScreen)
                {
                    if(collidingSprite != GetSprite(mCurrentGameState, "chart-editor-new-chart-user-interface"))
                        mShowNewChartScreen = false;

                }
            }
        }
    }
}

Sprite* Game::CheckCollidingSprite(GameState gameState)
{
    // Define relevant sprites for each game state
    std::vector<std::string> relevantSprites;

    if (gameState == GameState::START_MENU)
    {
        relevantSprites = {"start-button", "exit-button"};
    }
    else if (gameState == GameState::MAIN_MENU)
    {
        relevantSprites = {"main-menu-back-button", "main-menu-chart-editor-button", "main-menu-chart-selection-button", "main-menu-settings-button"};
    }
    else if (gameState == GameState::SETTINGS)
    {
        relevantSprites = {"settings-increment-left-1", "settings-increment-left-2", "settings-increment-left-3", "settings-increment-right-1", "settings-increment-right-2","settings-increment-right-3"};
    }
    else if (gameState == GameState::CHART_EDITOR_SELECTION_MENU)
    {
        relevantSprites = {"chart-editor-new-chart-button","chart-editor-selection-menu-ui","chart-editor-selection-menu-ua"};
    }

    // Check collision for relevant sprites
    for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[gameState])
    {
        if (std::find(relevantSprites.begin(), relevantSprites.end(), key) != relevantSprites.end())
        {
            bool CollisionX = (mMouse->GetMouseCoordinate().x + mMouse->GetMouseSize().x >= sprite->GetPosition().x) &&
                              (sprite->GetPosition().x + sprite->GetSize().x >= mMouse->GetMouseCoordinate().x);

            bool CollisionY = (mMouse->GetMouseCoordinate().y + mMouse->GetMouseSize().y >= sprite->GetPosition().y) &&
                              (sprite->GetPosition().y + sprite->GetSize().y >= mMouse->GetMouseCoordinate().y);

            if (CollisionX && CollisionY)
            {
                return sprite; // Return the first colliding sprite
            }
        }
    }

    return nullptr; // No collision detected
}
