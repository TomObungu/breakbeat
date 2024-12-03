#ifndef MENU_HPP
#define MENU_HPP

#include "Sprite.hpp"
#include <vector>

using std::vector;

#include <functional>

using Callback = std::function<void()>;

class Menu
{
public:
    Menu(vector<Sprite*>,bool);
    void AppendSprite(Sprite*);
    void IncrementMenuChoice();
    void DecrementMenuChoice();

    void SetHighlightAnimation(Callback animationCallback);
    void SetSelectionAnimation(Callback animationcCallback);
    void PlayHighlightAnimation();
    Sprite* GetCurrentMenuOption();
    
    void UpdateCurrentTime();
    void UpdateLastSelectedTime();
    bool CheckSelectionTime();

private:
    vector<Sprite*> mSprites;
    int mMenuChoice;
    Sprite* mCurrentlySelectedMenuChoice;
    bool mWrapAround;

    Callback mHighlightAnimation = nullptr;
    Callback mSelectionAnimation = nullptr;

    float mSelectionDelay = 200;     // Minimum delay between inputs in milliseconds
    Uint32 mLastSelectionTime = 0; 
    Uint32 mCurrentTime;
};

#endif  