#ifndef MENU_HPP
#define MENU_HPP

#include "Sprite.hpp"
#include "Text.hpp"
#include <vector>

using std::vector;

#include <functional>

using Callback = std::function<void()>;

class Menu
{
public:
    Menu(vector<Sprite*>,bool);
    Menu(vector<Text*>, bool);
    void AppendSprite(Sprite*);
    void AppendText(Text* text);
    void IncrementMenuChoice();
    void MoveMenuChoiceUp();
    void MoveMenuChoiceDown();
    void DecrementMenuChoice();

    void IncrementTextMenuChoice();
    void MoveTextMenuChoiceUp();
    void MoveTextMenuChoiceDown();
    void DecrementTextMenuChoice();

    void SetHighlightAnimation(Callback animationCallback);
    void SetSelectionAnimation(Callback animationcCallback);
    void SetCurrentMenuOption(Sprite*);
    void SetCurrentTextMenuOption(Text* sprite);

    void SetUnhighlightAnimation(Callback callback);
    void SetUnselectionAnimation(Callback callback);

    void PlayHighlightAnimation();
     void PlaySelectionAnimation();
    void PlayUnhighlightAnimation();
    void PlayUnselectionAnimation();

    Sprite* GetCurrentMenuOption();
    Text* GetCurrentTextOption();
    
    void UpdateCurrentTime();
    void UpdateLastSelectedTime();
    bool CheckSelectionTime();

private:
    vector<Sprite*> mSprites;
    vector<Text*> mTexts;
    int mMenuChoice = 0;
    int mTextMenuChoice = 0;
    Sprite* mCurrentlySelectedMenuChoice;
    Text* mCurrentlySelectedTextChoice;
    bool mWrapAround;
    int mHorizontalLength;
    int mVerticalLength;

    Callback mHighlightAnimation = nullptr;
    Callback mSelectionAnimation = nullptr;
    Callback mUnhighlightAnimation = nullptr;
    Callback mUnselectionAnimation = nullptr;

    float mSelectionDelay = 200;     // Minimum delay between inputs in milliseconds
    Uint32 mLastSelectionTime = 0; 
    Uint32 mCurrentTime;
};

#endif  