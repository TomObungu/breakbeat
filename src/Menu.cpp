#include "Menu.hpp"

Menu::Menu(vector<Sprite*> sprites, bool wrapAround)
    : mSprites(sprites),
      mWrapAround(wrapAround),
      mMenuChoice(0),
      mCurrentlySelectedMenuChoice(mSprites[mMenuChoice])
{
}

void Menu::AppendSprite(Sprite* sprite)
{
    mSprites.push_back(sprite);
}

void Menu::IncrementMenuChoice()
{
    if (mWrapAround)
    {
        mMenuChoice = (mMenuChoice + 1) % mSprites.size();
    }
    else
    {
        if (mMenuChoice < mSprites.size() - 1) 
        {
            ++mMenuChoice;
        }
    }
    mCurrentlySelectedMenuChoice = mSprites[mMenuChoice];
}

void Menu::DecrementMenuChoice()
{
    if (mWrapAround)
    {
        mMenuChoice = (mMenuChoice - 1 + mSprites.size()) % mSprites.size(); // Handle negative mod
    }
    else
    {
        if (mMenuChoice > 0) 
        {
            --mMenuChoice;
        }
    }
    mCurrentlySelectedMenuChoice = mSprites[mMenuChoice];
}

void Menu::SetHighlightAnimation(Callback callback)
{
    mSelectionAnimation = callback;
}

void Menu::SetSelectionAnimation(Callback callback)
{
    mHighlightAnimation = callback;
}

void Menu::PlayHighlightAnimation()
{
    if(mSelectionAnimation)
        mSelectionAnimation();
}

void Menu::UpdateCurrentTime()
{
    mCurrentTime = SDL_GetTicks();
}   

void Menu::UpdateLastSelectedTime()
{
    mLastSelectionTime = mCurrentTime;
}   

Sprite* Menu::GetCurrentMenuOption()
{
    return mCurrentlySelectedMenuChoice;
}

bool Menu::CheckSelectionTime()
{
    return (mCurrentTime - mLastSelectionTime >= mSelectionDelay);
}