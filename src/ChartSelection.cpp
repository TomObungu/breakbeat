#include "Game.hpp"

void Game::CheckNewChartButton()
{
    auto& table = mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState];
    auto& textTable =  mTextRenderer.mCurrentlyRenderedTexts[mCurrentGameState];

    if(mShowNewChartScreen)
    {
        if(!mTransitioningDark && !mAllDark)
        {
            mTransitioningDark = true;
            mAllLight = false;
            for (auto& [key, sprite] : table)
            {
                if(sprite != nullptr)
                    sprite->SetColor(vec3(0.5f));
            }
            for (auto& [key, text] : textTable)
            {
                if(text != nullptr)
                    text->SetColor(vec3(0.5f));
            }
            mTransitioningDark = false;
            mAllDark = true;
        }
        if(!mAddingSprites && !mNewChartSpritesOnScreen)
        {
            if(table.contains("z-chart-editor-new-chart-user-interface") ||
            table.contains("z-chart-editor-new-chart-create-button") || 
            table.contains("z-chart-editor-new-chart-create-button"))
            {
                mNewChartSpritesOnScreen = true;
            }
            mAddingSprites = true;
        }
        if(mAddingSprites && !mNewChartSpritesOnScreen)
        {
            table["z-chart-editor-new-chart-user-interface"] = GetDefaultSprite(mCurrentGameState,"z-chart-editor-new-chart-user-interface");
            table["zz-chart-editor-new-chart-create-button"] = GetDefaultSprite(mCurrentGameState,"zz-chart-editor-new-chart-create-button");
            table["zz-chart-editor-new-chart-user-interface-box-new-image"] = GetDefaultSprite(mCurrentGameState,"zz-chart-editor-new-chart-user-interface-box-new-image");
            textTable.erase("song-text-1");
            textTable.erase("artist-text-1");
            textTable.erase("song-text-2");
            textTable.erase("artist-text-2");
            textTable.erase("song-text-5");
            textTable.erase("artist-text-5");
            textTable["new-chart-screen-song-name-text"] = GetDefaultText(mCurrentGameState, "new-chart-screen-song-name-text");
            textTable["new-chart-screen-song-name-text-box"] = GetDefaultText(mCurrentGameState, "new-chart-screen-song-name-text-box");
            textTable["new-chart-screen-artist-name-text"] = GetDefaultText(mCurrentGameState, "new-chart-screen-artist-name-text");
            textTable["new-chart-screen-artist-name-text-box"] = GetDefaultText(mCurrentGameState, "new-chart-screen-artist-name-text-box");
            textTable["new-chart-screen-difficulty-name-text"] = GetDefaultText(mCurrentGameState, "new-chart-screen-difficulty-name-text");
            textTable["new-chart-screen-difficulty-name-text-box"] = GetDefaultText(mCurrentGameState, "new-chart-screen-difficulty-name-text-box");
            textTable["new-chart-screen-song-bpm-text"] = GetDefaultText(mCurrentGameState, "new-chart-screen-song-bpm-text");
            textTable["new-chart-screen-song-bpm-text-box"] = GetDefaultText(mCurrentGameState, "new-chart-screen-song-bpm-text-box");
            textTable["new-chart-screen-chart-image-text"] = GetDefaultText(mCurrentGameState, "new-chart-screen-chart-image-text");
            textTable["new-chart-screen-chart-audio-text"] = GetDefaultText(mCurrentGameState, "new-chart-screen-chart-audio-text");
            textTable["new-chart-screen-chart-audio-text"]->UpdateText("Audio : " + mNewChartAudioPath);
            mNewChartSpritesOnScreen = true;
            mAddingSprites = false;
        }
    }
    else 
    {
        if(table.contains("z-chart-editor-new-chart-user-interface") ||
            table.contains("zz-chart-editor-new-chart-create-button") ||
            table.contains("zz-chart-editor-new-chart-user-interface-box-new-image"))
        {
            for (auto& [key, sprite] : table)
            {
                table.erase("z-chart-editor-new-chart-user-interface");
                table.erase("zz-chart-editor-new-chart-create-button");
                table.erase("zz-chart-editor-new-chart-user-interface-box-new-image");

                textTable.erase("new-chart-screen-song-name-text");
                textTable.erase("new-chart-screen-song-name-text-box");
                mNewChartSongName = "";
                textTable.erase("new-chart-screen-artist-name-text");
                textTable.erase("new-chart-screen-artist-name-text-box");
                mNewChartArtistName = "";
                textTable.erase("new-chart-screen-difficulty-name-text");
                textTable.erase("new-chart-screen-difficulty-name-text-box");
                mNewChartDifficultyName = "";
                textTable.erase("new-chart-screen-song-bpm-text");
                textTable.erase("new-chart-screen-song-bpm-text-box");
                mNewChartBPM = "";
                textTable.erase("new-chart-screen-chart-image-text");
                textTable.erase("new-chart-screen-chart-audio-text");
            }
            mNewChartSpritesOnScreen = false;
        }
        textTable["song-text-1"] = GetDefaultText(mCurrentGameState, "song-text-1");
        textTable["artist-text-1"] = GetDefaultText(mCurrentGameState, "artist-text-1");
        textTable["song-text-2"] = GetDefaultText(mCurrentGameState, "song-text-2");
        textTable["artist-text-2"] = GetDefaultText(mCurrentGameState, "artist-text-2");
        textTable["song-text-5"] = GetDefaultText(mCurrentGameState, "song-text-5");
        textTable["artist-text-5"] = GetDefaultText(mCurrentGameState, "artist-text-5"); 
        if(!mTransitioningLight && !mAllLight) 
        {
            mTransitioningLight = true;
            for (auto& [key, sprite] : table)
            {
                if(sprite != nullptr)
                    sprite->SetColor(vec3(1.0f));
            }
            for (auto& [key, text] : mTextRenderer.mCurrentlyRenderedTexts[mCurrentGameState])
            {
                if(text != nullptr)
                    text->SetColor(vec3(1.0f));
            }
            mTransitioningLight = false;
            mAllLight = true;
            mAllDark = false;
        }
    }
}