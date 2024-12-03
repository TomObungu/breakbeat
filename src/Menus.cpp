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

    Menu* startMenu = GetMenu(mCurrentGameState, "start-menu");

    startMenu->SetHighlightAnimation(
        [this,startMenu](){
        startMenu->GetCurrentMenuOption()->SetColor(vec3(1.0f, 1.0f, 0.0f));
    });
}