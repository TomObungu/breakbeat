#include "Game.hpp"

void Game::LoadBackgroundImage()
{
	Texture bgImage = ResourceManager::loadTextureFromFile((fs::current_path().string() + "/charts/Sharkey & Architech-Quadraphinix/quad-BG.jpg").c_str(), false);
	GetSprite(mCurrentGameState, "main-gameplay-background-image")->SetTexture(bgImage);
}

void Game::InitializeMainGameplay()
{
    // Load the background image
    LoadBackgroundImage();

    vec2 receptorSize = vec2(192.000 * (mReceptorSize / 100.0f), 180 * (mReceptorSize / 100.0f));

    GetSprite(mCurrentGameState, "main-gameplay-left-note-receptor")->SetSize(receptorSize);
    GetSprite(mCurrentGameState, "main-gameplay-left-note-receptor")->SetPosition(vec2(581.936, ((mReceptorSize / 100.0f) * -192.565) + 1080));
    GetSprite(mCurrentGameState, "z-main-gameplay-down-note-receptor")->SetSize(receptorSize);
	GetSprite(mCurrentGameState, "z-main-gameplay-down-note-receptor")->SetPosition(vec2(((mReceptorSize / 100.0f) - 1) * 183.487 + 765.423, ((mReceptorSize / 100) * -192.565) +1080));
    GetSprite(mCurrentGameState, "main-gameplay-up-note-receptor")->SetSize(receptorSize);
    GetSprite(mCurrentGameState, "main-gameplay-up-note-receptor")->SetPosition(vec2(((mReceptorSize / 100.0f) - 1) * 366.974 + 949.361, ((mReceptorSize / 100) * -192.565) +1080));
    GetSprite(mCurrentGameState, "main-gameplay-right-note-receptor")->SetSize(receptorSize);
    GetSprite(mCurrentGameState, "main-gameplay-right-note-receptor")->SetPosition(vec2(((mReceptorSize / 100.0f) - 1) * 550.461 + 1138.061, ((mReceptorSize / 100) * -192.565) +1080));
    GetSprite(mCurrentGameState, "main-gameplay-gameplay-vsrg-column")->SetSize(vec2(755.998 * (mReceptorSize / 100), 1080));

    // Reset song start time
   
    float totalDistance = 180 * (mReceptorSize / 100) + ((mReceptorSize / 100.0f) * -192.565) + 1080; // Adjusted for note height and receptor size
    float timeTakenToFall = (totalDistance / mScrollSpeed) * 1000; // Convert to milliseconds
     
    for (auto& time : firstColumnNoteHitTimes)
    {
        firstColumnNoteRenderTimes.push_back(time - timeTakenToFall);
        // time -= (192.535 * (mReceptorSize / 100) / mScrollSpeed) * 1000;
    }
    for (auto& time : secondColumnNoteHitTimes)
    {
        secondColumnNoteRenderTimes.push_back(time - timeTakenToFall);
        // time -= (192.565 * (mReceptorSize / 100) / mScrollSpeed) * 1000;
    }
    for (auto& time : thirdColumnNoteHitTimes)
    {
        thirdColumnNoteRenderTimes.push_back(time - timeTakenToFall);
        // time -= (192.565 * (mReceptorSize / 100) / mScrollSpeed) * 1000;
    }
    for (auto& time : fourthColumnNoteHitTimes)
    {
        fourthColumnNoteRenderTimes.push_back(time - timeTakenToFall);
        // time -= (192.565 * (mReceptorSize / 100) / mScrollSpeed) * 1000;
    }

    // Initialize the note rendering system
}

void Game::HandleMainGameplay()
{

    GetText(mCurrentGameState, "gameplay-time-elapsed")->UpdateText(to_string(mTimeElapsed));

    // Update the time elapsed

    // Render notes
    RenderNotes();

    HandleMissedHitRegistration();
}


void Game::RenderNotes()
{

    if (!mSongPlaying)
    {
        mSoundEngine->play2D("C:\\Users\\deeza\\AppData\\Local\\osu!\\Songs\\828129 Sharkey & Arkitech - Quadraphinix\\Quadraphinix_0 0.750x.mp3", false);
        mSongStartTime = SDL_GetTicks();
        mSongPlaying = true;
    }

    if (mSongPlaying)
        mTimeElapsed = SDL_GetTicks() - mSongStartTime;

    // Calculate the time it takes for a note to fall from the top to the receptor

    if (firstColumnNextNoteRenderIndex < firstColumnNoteRenderTimes.size() &&
        mTimeElapsed >= (firstColumnNoteRenderTimes[firstColumnNextNoteRenderIndex]))
    {
        string noteName = "main-gameplay-left-note-" + to_string(firstColumnNextNoteRenderIndex);
        mSpriteRenderer.CreateNote(
            GameState::MAIN_GAMEPLAY,
            noteName,
            ResourceManager::GetTexture("main-gameplay-left-note"),
            vec2(581.936, -180 * (mReceptorSize / 100)), // Start position at the top
            vec2(192.000 * (mReceptorSize / 100), 180 * (mReceptorSize / 100)),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );

        firstColumnNextNoteRenderIndex++;
    }   

    if (secondColumnNextNoteRenderIndex < secondColumnNoteRenderTimes.size() &&
        mTimeElapsed >= (secondColumnNoteRenderTimes[secondColumnNextNoteRenderIndex]))
    {
        string noteName = "main-gameplay-down-note-" + to_string(secondColumnNextNoteRenderIndex);
        mSpriteRenderer.CreateNote(
            GameState::MAIN_GAMEPLAY,
            noteName,
            ResourceManager::GetTexture("main-gameplay-down-note"),
            vec2(((mReceptorSize / 100.0f) - 1) * 183.487 + 765.423, -180 * (mReceptorSize / 100)), // Start position at the top
            vec2(192.000 * (mReceptorSize / 100), 180 * (mReceptorSize / 100)),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );

        secondColumnNextNoteRenderIndex++;
    }  

    if (thirdColumnNextNoteRenderIndex < thirdColumnNoteRenderTimes.size() &&
        mTimeElapsed >= (thirdColumnNoteRenderTimes[thirdColumnNextNoteRenderIndex])) 
    {
        string noteName = "main-gameplay-up-note-" + to_string(thirdColumnNextNoteRenderIndex);
        mSpriteRenderer.CreateNote(
            GameState::MAIN_GAMEPLAY,
            noteName,
            ResourceManager::GetTexture("main-gameplay-up-note"),
            vec2(((mReceptorSize / 100.0f) - 1) * 366.974 + 949.361, -180 * (mReceptorSize / 100)), // Start position at the top
            vec2(192.000 * (mReceptorSize / 100), 180 * (mReceptorSize / 100)),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );

        thirdColumnNextNoteRenderIndex++;
    }  

    if (fourthColumnNextNoteRenderIndex < fourthColumnNoteRenderTimes.size() &&
        mTimeElapsed >= (fourthColumnNoteRenderTimes[fourthColumnNextNoteRenderIndex]))
    {
        string noteName = "main-gameplay-right-note-" + to_string(fourthColumnNextNoteRenderIndex);
        mSpriteRenderer.CreateNote(
            GameState::MAIN_GAMEPLAY,
            noteName,
            ResourceManager::GetTexture("main-gameplay-right-note"),
            vec2(((mReceptorSize / 100.0f) - 1) * 550.461 + 1138.061, -180 * (mReceptorSize / 100)), // Start position at the top
            vec2(192.000 * (mReceptorSize / 100), 180 * (mReceptorSize / 100)),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );

        fourthColumnNextNoteRenderIndex++;
    }

    // Move all notes based on scroll speed and delta time
    for (auto& [key, note] : mSpriteRenderer.mNoteBuffer[mCurrentGameState])
    {
        if (note != nullptr)
        {
            // Calculate how far the note moves this frame
            note->Move(vec2(0, mScrollSpeed * (mDeltaTime / 1000.0f)));

        }
    }
}

void Game::HandleHitRegistration(SDL_Event& event)
{
    HitNoteInFirstColumn = false;
    if (SDL_GetKeyName(event.key.keysym.sym) == mLeftKeybind)
    {
        firstColumnHitTime = mTimeElapsed;
        firstColumnHitDifference = abs(firstColumnHitTime - firstColumnNoteHitTimes[firstColumnNextNoteTimeIndex]);
		std::cout << "The note time is : " << firstColumnHitTime << " The hit difference is : " << firstColumnHitDifference << '\n';
        if (firstColumnHitDifference <= 180)
        {
            HitNoteInFirstColumn = true;
            mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase("main-gameplay-left-note-" + to_string(firstColumnNextNoteTimeIndex));
            if (firstColumnNextNoteTimeIndex < firstColumnNoteHitTimes.size())
                firstColumnNextNoteTimeIndex++;
            if (firstColumnHitDifference >= 0 && firstColumnHitDifference <= 18.9 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
            }            
            else if (firstColumnHitDifference > 18.9 && firstColumnHitDifference <= 37.8)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
            }            
            else if(firstColumnHitDifference > 37.8 && firstColumnHitDifference <= 75.6)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
            }            
            if(firstColumnHitDifference > 75.6 && firstColumnHitDifference <= 113.4 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
            }            
            if(firstColumnHitDifference > 113.4 && firstColumnHitDifference <= 180 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
            }
        }
    }    

    HitNoteInSecondColumn = false;
    if (SDL_GetKeyName(event.key.keysym.sym) == mDownKeybind)
    {
        secondColumnHitTime = mTimeElapsed;
        secondColumnHitDifference = abs(secondColumnHitTime - secondColumnNoteHitTimes[secondColumnNextNoteTimeIndex]);
        std::cout << "The note time is : " << firstColumnHitTime << " The hit difference is : " << firstColumnHitDifference << '\n';
        if (secondColumnHitDifference <= 180)
        {
            HitNoteInSecondColumn = true;
            mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase("main-gameplay-down-note-" + to_string(secondColumnNextNoteTimeIndex));
            if (secondColumnNextNoteTimeIndex < secondColumnNoteHitTimes.size())
                secondColumnNextNoteTimeIndex++;
            if (secondColumnHitDifference >= 0 && secondColumnHitDifference <= 18.9 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
            }            
            else if (secondColumnHitDifference > 18.9 && secondColumnHitDifference <= 37.8)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
            }            
            else if(secondColumnHitDifference > 37.8 && secondColumnHitDifference <= 75.6)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
            }            
            if(secondColumnHitDifference > 75.6 && secondColumnHitDifference <= 113.4 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
            }            
            if(secondColumnHitDifference > 113.4 && secondColumnHitDifference <= 180 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
            }
        }
    }    
    
    HitNoteInFirstColumn = false;
    if (SDL_GetKeyName(event.key.keysym.sym) == mUpKeybind)
    {
        thirdColumnHitTime = mTimeElapsed;
        thirdColumnHitDifference = abs(thirdColumnHitTime - thirdColumnNoteHitTimes[thirdColumnNextNoteTimeIndex]);
        std::cout << "The note time is : " << firstColumnHitTime << " The hit difference is : " << firstColumnHitDifference << '\n';
        if (thirdColumnHitDifference <= 180)
        {
            HitNoteInFirstColumn = true;
            mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase("main-gameplay-up-note-" + to_string(thirdColumnNextNoteTimeIndex));
            if (thirdColumnNextNoteTimeIndex < thirdColumnNoteHitTimes.size())
                thirdColumnNextNoteTimeIndex++;
            if (thirdColumnHitDifference >= 0 && thirdColumnHitDifference <= 18.9 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
            }            
            else if (thirdColumnHitDifference > 18.9 && thirdColumnHitDifference <= 37.8)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
            }            
            else if(thirdColumnHitDifference > 37.8 && thirdColumnHitDifference <= 75.6)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
            }            
            if(thirdColumnHitDifference > 75.6 && thirdColumnHitDifference <= 113.4 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
            }            
            if(thirdColumnHitDifference > 113.4 && thirdColumnHitDifference <= 180 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
            }
        }
    }    

    HitNoteInSecondColumn = false;
    if (SDL_GetKeyName(event.key.keysym.sym) == mRightKeybind)
    {
        fourthColumnHitTime = mTimeElapsed;
        fourthColumnHitDifference = abs(fourthColumnHitTime - fourthColumnNoteHitTimes[fourthColumnNextNoteTimeIndex]);
        std::cout << "The note time is : " << firstColumnHitTime << " The hit difference is : " << firstColumnHitDifference << '\n';
        if (fourthColumnHitDifference <= 180)
        {
            HitNoteInSecondColumn = true;
            mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase("main-gameplay-right-note-" + to_string(fourthColumnNextNoteTimeIndex));
            if (fourthColumnNextNoteTimeIndex < fourthColumnNoteHitTimes.size())
                fourthColumnNextNoteTimeIndex++;
            if (fourthColumnHitDifference >= 0 && fourthColumnHitDifference <= 18.9 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
            }            
            else if (fourthColumnHitDifference > 18.9 && fourthColumnHitDifference <= 37.8)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
            }            
            else if(fourthColumnHitDifference > 37.8 && fourthColumnHitDifference <= 75.6)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
            }            
            if(fourthColumnHitDifference > 75.6 && fourthColumnHitDifference <= 113.4 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
            }            
            if(fourthColumnHitDifference > 113.4 && fourthColumnHitDifference <= 180 )
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
            }
        }
    }
}

void Game::HandleMissedHitRegistration()
{

    if (firstColumnNextNoteTimeIndex < firstColumnNoteHitTimes.size())
    {
        if (mTimeElapsed > firstColumnNoteHitTimes[firstColumnNextNoteTimeIndex] + 180)
        {
            firstColumnNextNoteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }    
    if (secondColumnNextNoteTimeIndex < secondColumnNoteHitTimes.size())
    {
        if (mTimeElapsed > secondColumnNoteHitTimes[secondColumnNextNoteTimeIndex] + 180)
        {
            secondColumnNextNoteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }    
    if (thirdColumnNextNoteTimeIndex < thirdColumnNoteHitTimes.size())
    {
        if (mTimeElapsed > thirdColumnNoteHitTimes[thirdColumnNextNoteTimeIndex] + 180)
        {
            thirdColumnNextNoteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }    
    if (fourthColumnNextNoteTimeIndex < fourthColumnNoteHitTimes.size())
    {
        if (mTimeElapsed > fourthColumnNoteHitTimes[fourthColumnNextNoteTimeIndex] + 180)
        {
            fourthColumnNextNoteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }
}



