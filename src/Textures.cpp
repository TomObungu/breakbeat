#include "Game.hpp"

void Game::InitializeTextures()
{
    // load textures

    /* MOUSE */
    ResourceManager::LoadTexture("\\assets\\png\\mouse\\cursor.png",true,"cursor");
    
    /* START MENU */
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-dots-dots-cropped.png",true,"background-dots");
    ResourceManager::LoadTexture("\\assets\\png\\breakbeat-background-arrows-squares-edit-cropped.png",true,"background");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-logo-2x-new.png", true, "game-logo");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-start-button.png", true, "start-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-exit-button.png", true, "exit-button");
    ResourceManager::LoadTexture("\\assets\\png\\start menu\\breakbeat-start-menu-user-navigation-assist.png", true, "start-menu-ua");

    /* MAIN MENU */
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-user-navigation-assist-new.png",true,"main-menu-ua");
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-settings-user-interface.png",true,"main-menu-settings-button");
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-chart-editor-user-interface.png",true,"main-menu-chart-editor-button");
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-chart-selection-user-interface.png",true,"main-menu-chart-selection-button");
    ResourceManager::LoadTexture("\\assets\\png\\main menu\\breakbeat-main-menu-back-button-user-interface.png",true,"main-menu-back-button");

    /* SETTINGS MENU */
    ResourceManager::LoadTexture("\\assets\\png\\settings menu\\breakbeat-settings-user-navigation-assist.png",true,"settings-menu-ua");
    ResourceManager::LoadTexture("\\assets\\png\\settings menu\\breakbeat-settings-information-text-2.png",true,"settings-menu-text");
    ResourceManager::LoadTexture("\\assets\\png\\settings menu\\breakbeat-settings-increment-right.png",true,"settings-increment-right");
    ResourceManager::LoadTexture("\\assets\\png\\settings menu\\breakbeat-settings-increment-left.png",true,"settings-increment-left");

    /* CHART EDITOR SELECTION MENU */
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-editor-menu-chart-selection-highlighted.png", true, "chart-editor-selection-menu-highlight");
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-editor-menu-chart-selection-interface.png", true, "chart-editor-selection-menu-ui");
    ResourceManager::LoadTexture("\\assets\\png\\chart selection menu\\breakbeat-chart-editor-menu-user-navigation-assist-new-2.png",true,"chart-editor-selection-menu-ua");
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-editor-new-chart-button.png",true,"chart-editor-new-chart-button");
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-editor-new-chart-user-interface-box.png",true,"chart-editor-new-chart-user-interface");
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-editor-new-chart-user-interface-box-create-button.png",true,"chart-editor-new-chart-create-button");
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-editor-new-chart-user-interface-box-new-image.png",true,"chart-editor-new-chart-user-interface-box-new-image");

    

}