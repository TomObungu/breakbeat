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
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-editor-new-difficullty-user-interface-box.png", true, "chart-editor-new-difficullty-user-interface-box");
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-editor-new-chart-user-interface-box-new-image.png", true, "chart-editor-new-chart-user-interface-box-new-image");   
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-selection-difficulty-select-box.png",true, "chart-selection-difficulty-select-box");
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-editor-menu-difficulty-new-difficulty-button.png",true, "chart-editor-menu-difficulty-new-difficulty-button");
    ResourceManager::LoadTexture("\\assets\\png\\chart editor menu\\breakbeat-chart-selection-difficulty-select-box-highlighted.png",true, "chart-selection-difficulty-select-box-highlighted");

    /* CHART SELECTION */
    ResourceManager::LoadTexture("\\assets\\png\\chart selection menu\\breakbeat-chart-selection-menu-user-navigation-assist-new.png", true, "chart-selection-menu-ua");
    ResourceManager::LoadTexture("\\assets\\png\\chart selection menu\\breakbeat-chart-selection-song-cover-frame.png", true, "song-cover-frame");
    ResourceManager::LoadTexture("\\assets\\png\\chart selection menu\\breakbeat-chart-selection-song-cover-texture.png", true, "song-cover");

    /* MAIN GAMEPLAY */
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-gameplay-vsrg-column.png",true,"main-gameplay-gameplay-vsrg-column");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-left-note.png",true,"main-gameplay-left-note");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-left-note-receptor.png",true,"main-gameplay-left-note-receptor" );
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-life-bar.png",true,"main-gameplay-life-bar");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-life-bar-handle.png",true,"main-gameplay-life-bar-handle");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-right-note.png",true,"main-gameplay-right-note");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-right-note-receptor.png",true,"main-gameplay-right-note-receptor");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-up-note.png",true,"main-gameplay-up-note");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-up-note-receptor.png",true,"main-gameplay-up-note-receptor");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-down-note.png",true,"main-gameplay-down-note");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-down-note-receptor.png",true,"main-gameplay-down-note-receptor");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-gameplay-statistics-box.png",true,"main-gameplay-gameplay-statistics-box");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\flawless.png", true, "flawless-judgement-text");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\good.png", true, "good-judgement-text");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\great.png", true, "great-judgement-text");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\miss.png", true, "miss-judgement-text");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\perfect.png", true, "perfect-judgement-text");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\bad.png", true, "bad-judgement-text");
    ResourceManager::LoadTexture("\\assets\\png\\transparent-texture.png", true, "transparent-texture");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\main-gameplay-hold-note-body.png", true, "main-gameplay-hold-note-body");

    /* CHART EDITOR */
    ResourceManager::LoadTexture("\\assets\\png\\chart editing\\breakbeat-chart-editing-scroll-bar-background.png", true, "chart-editing-scroll-bar-background");
    ResourceManager::LoadTexture("\\assets\\png\\chart editing\\breakbeat-chart-editing-beat-snap-bar.png", true, "chart-editing-beat-snap-bar");
    ResourceManager::LoadTexture("\\assets\\png\\chart editing\\breakbeat-chart-editing-scroll-bar.png", true, "chart-editing-scroll-bar");
    ResourceManager::LoadTexture("\\assets\\png\\chart editing\\breakbeat-chart-editing-scroll-bar-handle.png", true, "breakbeat-chart-editing-scroll-bar-handle");

    /* GRADE SCREEN */
    ResourceManager::LoadTexture("\\assets\\png\\grade screen\\breakbeat-main-gameplay-grade-screen-box.png", true, "main-gameplay-grade-screen-box");
    ResourceManager::LoadTexture("\\assets\\png\\grade screen\\breakbeat-main-gameplay-grade-screen-user-navigation-assist.png", true, "main-gameplay-grade-screen-ua");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-grade-screen-A.png", true, "main-gameplay-grade-screen-A");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-grade-screen-B.png", true, "main-gameplay-grade-screen-B");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-grade-screen-C.png", true, "main-gameplay-grade-screen-C");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-grade-screen-D.png", true, "main-gameplay-grade-screen-D");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-grade-screen-F.png", true, "main-gameplay-grade-screen-F");
    ResourceManager::LoadTexture("\\assets\\png\\gameplay design\\breakbeat-main-gameplay-grade-screen-S.png", true, "main-gameplay-grade-screen-S");
}