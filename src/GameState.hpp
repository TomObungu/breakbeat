#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

enum class GameState {
    START_MENU,
    MAIN_GAMEPLAY,
    MAIN_MENU,
    SETTINGS,
    CHART_SELECTION_MENU,
    CHART_EDITOR_SELECTION_MENU,
    CHART_EDITOR,
    NOT_TRANSITIONING
};

#endif