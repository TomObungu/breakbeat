#include "Menu.hpp"

Menu::Menu(vector<Sprite*> sprites, bool wrapAround)
    : mSprites(sprites),
      mWrapAround(wrapAround),
      mMenuChoice(0),
      mCurrentlySelectedMenuChoice(mSprites[mMenuChoice])
{
    mHorizontalLength = 2;
}

Menu::Menu(vector<Text*> texts, bool wrapAround)
    : mTexts(texts),
      mWrapAround(wrapAround),
      mTextMenuChoice(0),
      mCurrentlySelectedTextChoice(mTexts[mTextMenuChoice])
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

void Menu::MoveMenuChoiceUp()
{
    int totalItems = mSprites.size(); // Get totalItems 
 
    if (mWrapAround) // If menu wrap around is true
    {   
        // Minus the length of the menu and the length of the menu columns
        mMenuChoice = (mMenuChoice - mHorizontalLength + totalItems) % totalItems; 
    }
    else
    {   
        if (mMenuChoice >= mHorizontalLength)
        {
            mMenuChoice -= mHorizontalLength;
        }
    }

    mCurrentlySelectedMenuChoice = mSprites[mMenuChoice];
}

void Menu::MoveMenuChoiceDown()
{
    int totalItems = mSprites.size();

    if (mWrapAround)
    {
        mMenuChoice = (mMenuChoice + mHorizontalLength) % totalItems;
    }
    else
    {
        if (mMenuChoice + mHorizontalLength < totalItems)
        {
            mMenuChoice += mHorizontalLength;
        }
    }

    mCurrentlySelectedMenuChoice = mSprites[mMenuChoice];
}

void Menu::AppendText(Text* text)
{
    mTexts.push_back(text);
}

void Menu::IncrementTextMenuChoice()
{
    if (mWrapAround)
    {
        mTextMenuChoice = (mTextMenuChoice + 1) % mTexts.size();
    }
    else
    {
        if (mTextMenuChoice < mTexts.size() - 1) 
        {
            ++mTextMenuChoice;
        }
    }
    mCurrentlySelectedTextChoice = mTexts[mTextMenuChoice];
}

void Menu::MoveTextMenuChoiceUp()
{
    int totalTextItems = mTexts.size(); // Get totalTextItems 
 
    if (mWrapAround) // If menu wrap around is true
    {   
        // Minus the length of the menu and the length of the menu columns
        mTextMenuChoice = (mTextMenuChoice - mHorizontalLength + totalTextItems) % totalTextItems; 
    }
    else
    {   
        if (mTextMenuChoice >= mHorizontalLength)
        {
            mTextMenuChoice -= mHorizontalLength;
        }
    }

    mCurrentlySelectedTextChoice = mTexts[mMenuChoice];
    
}

void Menu::MoveTextMenuChoiceDown()
{

    int totalTextItems = mTexts.size();

    if (mWrapAround)
    {
        mTextMenuChoice = (mTextMenuChoice + mHorizontalLength) % totalTextItems;
    }
    else
    {
        if (mTextMenuChoice + mHorizontalLength < totalTextItems)
        {
            mTextMenuChoice += mHorizontalLength;
        }
    }

    mCurrentlySelectedTextChoice = mTexts[mTextMenuChoice];
}

void Menu::DecrementTextMenuChoice()
{
    if (mWrapAround)
    {
        mTextMenuChoice = (mTextMenuChoice - 1 + mTexts.size()) % mTexts.size(); // Handle negative mod
    }
    else
    {
        if (mTextMenuChoice > 0) 
        {
            --mTextMenuChoice;
        }
    }
    mCurrentlySelectedTextChoice = mTexts[mTextMenuChoice];
}

Text* Menu::GetCurrentTextOption()
{
    return mCurrentlySelectedTextChoice;
}

void Menu::SetHighlightAnimation(Callback callback)
{
    mHighlightAnimation = callback;
}

void Menu::SetSelectionAnimation(Callback callback)
{
    mSelectionAnimation = callback;
}

void Menu::SetUnhighlightAnimation(Callback callback)
{
    mUnhighlightAnimation = callback;
}

void Menu::SetUnselectionAnimation(Callback callback)
{
    mUnselectionAnimation = callback;
}

void Menu::PlayHighlightAnimation()
{
    if(mHighlightAnimation)
        mHighlightAnimation();
}

void Menu::PlaySelectionAnimation()
{
    if(mSelectionAnimation)
        mSelectionAnimation();
}

void Menu::PlayUnhighlightAnimation()
{
    if(mUnhighlightAnimation)
        mUnhighlightAnimation();
}

void Menu::PlayUnselectionAnimation()
{
    if(mUnselectionAnimation)
        mUnselectionAnimation();
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

void Menu::SetCurrentMenuOption(Sprite* sprite)
{
    mCurrentlySelectedMenuChoice = sprite;
}

void Menu::SetCurrentTextMenuOption(Text* text)
{
    mCurrentlySelectedTextChoice = text;
}