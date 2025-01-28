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
    GetSprite(mCurrentGameState, "main-gameplay-left-note-receptor")->SetPosition(vec2(581.936, ((mReceptorSize / 100.0f) * -180) + 1080));
    GetSprite(mCurrentGameState, "z-main-gameplay-down-note-receptor")->SetSize(receptorSize);
	GetSprite(mCurrentGameState, "z-main-gameplay-down-note-receptor")->SetPosition(vec2(((mReceptorSize / 100.0f) - 1) * 183.487 + 765.423, ((mReceptorSize / 100) * -180) + 1080));
    GetSprite(mCurrentGameState, "main-gameplay-up-note-receptor")->SetSize(receptorSize);
    GetSprite(mCurrentGameState, "main-gameplay-up-note-receptor")->SetPosition(vec2(((mReceptorSize / 100.0f) - 1) * 366.974 + 949.361, ((mReceptorSize / 100) * -180) + 1080));
    GetSprite(mCurrentGameState, "main-gameplay-right-note-receptor")->SetSize(receptorSize);
    GetSprite(mCurrentGameState, "main-gameplay-right-note-receptor")->SetPosition(vec2(((mReceptorSize / 100.0f) - 1) * 550.461 + 1138.061, ((mReceptorSize / 100) * -180) + 1080));
    GetSprite(mCurrentGameState, "main-gameplay-gameplay-vsrg-column")->SetSize(vec2(755.998 * (mReceptorSize / 100), 1080));

    
    mTimeTakenToFall = (1080 / mScrollSpeed) * 1000; // Time taken to fall in milliseconds
        
    for (unsigned i = 0; i < 4; i++)
    {
        mNoteColumns[i].xPos = i > 0 ? 581.936 + (i * 183.944) + ((mReceptorSize / 100.0f) - 1) * (i * 183.487) : 581.936;
    }
    for (unsigned i = 0; i < 4; i++)
    {
        for (auto& time : mNoteColumns[i].hitTimes)
        {
			mNoteColumns[i].renderTimes.push_back(time - mTimeTakenToFall);
        }
    }

    mSoundEngine->play2D("C:\\Users\\deeza\\AppData\\Local\\osu!\\Songs\\919633 xi - Blue Zenith\\audio.mp3", false);
    mSongStartTime = SDL_GetTicks();
    mSongPlaying = true;
}

void Game::HandleMainGameplay()
{
    // Update the time elapsed
    mTimeElapsed = SDL_GetTicks() - mSongStartTime;

    GetText(mCurrentGameState, "gameplay-time-elapsed")->UpdateText("Time Elapsed : " + to_string(mTimeElapsed));

    HandleMissedHitRegistration();

    // Render notes
    RenderNotes();

    
}

// Main logic

void Game::RenderNotes()
{
    // Calculate the time it takes for a note to fall from the top to the receptor
    for (auto& noteColumn : mNoteColumns)
    {
        RenderNote(noteColumn);
    }

    // Move all notes based on scroll speed and delta time
    for (auto& [key, note] : mSpriteRenderer.mNoteBuffer[mCurrentGameState])
    {
        if(note!=nullptr)
            if (note->mIsMoving)
                note->Move(vec2(0,mScrollSpeed * mDeltaTime / 1000.f));
    }
}

void Game::RenderNote(NoteColumn& noteColumn)
{
    float totalDistance = 1080; // Adjusted for note height and receptor size
    float mTimeTakenToFall = (totalDistance / mScrollSpeed) * 1000; // Time taken to fall in milliseconds
    if (noteColumn.renderTimeIndex < noteColumn.renderTimes.size() &&  
            mTimeElapsed >= (noteColumn.renderTimes[noteColumn.renderTimeIndex]))
    {
        mSpriteRenderer.CreateNote(
            mCurrentGameState,
            noteColumn.noteName + '-' + to_string(noteColumn.renderTimeIndex),
            ResourceManager::GetTexture(noteColumn.noteName),
            vec2(noteColumn.xPos, -180 * (mReceptorSize / 100)), // Start position at the top
            vec2(192.000 * (mReceptorSize / 100.0f), 180 * (mReceptorSize / 100.0f)),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );
        noteColumn.renderTimeIndex++;
    }

    // Check if it's time to create the long note head (hit time)
    if (noteColumn.longNoteRenderTimeIndex < noteColumn.longNoteHitTimes.size() && 
            mTimeElapsed >= (noteColumn.longNoteHitTimes[noteColumn.longNoteRenderTimeIndex] - mTimeTakenToFall)) {
        mSpriteRenderer.CreateNote(
            mCurrentGameState,
            noteColumn.noteName + "-long-note-head-" + to_string(noteColumn.longNoteRenderTimeIndex),
            ResourceManager::GetTexture(noteColumn.noteName),
            vec2(noteColumn.xPos, -180 * (mReceptorSize / 100)), // Start position at the top
            vec2(192.000 * (mReceptorSize / 100.0f), 180 * (mReceptorSize / 100.0f)),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );

        float timeDifference = noteColumn.releaseTimes[noteColumn.releaseTimeRenderTimeIndex] -
            noteColumn.longNoteHitTimes[noteColumn.longNoteRenderTimeIndex];

        // Avoid negative or zero body size for very short long notes
        float bodyHeight = abs(timeDifference * mScrollSpeed / 1000.0f);

        mSpriteRenderer.CreateNote(
            GameState::MAIN_GAMEPLAY,
            noteColumn.noteName + "-long-note-body-" + to_string(noteColumn.longNoteRenderTimeIndex),
            ResourceManager::GetTexture("main-gameplay-hold-note-body"),
            vec2(noteColumn.xPos, -90 * (mReceptorSize / 100)), // Start position at the top
            vec2(192 * (mReceptorSize / 100), -bodyHeight),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );
        
        noteColumn.releaseTimeRenderTimeIndex++;
        noteColumn.longNoteRenderTimeIndex++;
    }
}

void Game::RegisterHit(NoteColumn& noteColumn)
{
    if (noteColumn.noteTimeIndex < noteColumn.hitTimes.size())
    {
        noteColumn.hitTime = mTimeElapsed;
        noteColumn.hitDifference = abs(noteColumn.hitTime - noteColumn.hitTimes[noteColumn.noteTimeIndex]);
        if (noteColumn.hitDifference <= 180)
        {
            noteColumn.hitNote = true;
            // std::cout << "You hit " << noteColumn.noteName + '-' + to_string(noteColumn.noteTimeIndex) << " at " << mTimeElapsed << " and a hit difference of " << noteColumn.hitDifference << " but the time supposed to be hit is " << noteColumn.hitTimes[noteColumn.noteTimeIndex] << '\n';
            mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase(noteColumn.noteName + '-' + to_string(noteColumn.noteTimeIndex));
            if (noteColumn.noteTimeIndex < noteColumn.hitTimes.size())
                noteColumn.noteTimeIndex++;
            if (noteColumn.hitDifference >= 0 && noteColumn.hitDifference <= 18.9)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
            }
            else if (noteColumn.hitDifference > 18.9 && noteColumn.hitDifference <= 37.8)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
            }
            else if (noteColumn.hitDifference > 37.8 && noteColumn.hitDifference <= 75.6)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
            }
            else if (noteColumn.hitDifference > 75.6 && noteColumn.hitDifference <= 113.4)
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
            }
            else
            {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
            }
        }
    }
    if (noteColumn.longNoteTimeIndex < noteColumn.longNoteHitTimes.size())
    {
        noteColumn.longNoteHitTime = mTimeElapsed;
        noteColumn.hitDifference = abs(noteColumn.longNoteHitTime - noteColumn.longNoteHitTimes[noteColumn.longNoteTimeIndex]);

        if (noteColumn.hitDifference <= 180) { // Within hit window
   
            // Stop the long note movement
            mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase(
                noteColumn.noteName + "-long-note-head-" + to_string(noteColumn.longNoteTimeIndex)
            );

            // Start shrinking logic
            auto& note = mSpriteRenderer.mNoteBuffer[mCurrentGameState][
                noteColumn.noteName + "-long-note-body-" + to_string(noteColumn.releaseTimeIndex)
            ];

            if (note == nullptr)
                noteColumn.releaseTimeIndex -= 1;
            
            if (note != nullptr)
            {
                noteColumn.longNoteOriginalHeight = note->GetSize().y;
                noteColumn.shrinkDuration = noteColumn.releaseTimes[noteColumn.releaseTimeIndex] -
                    noteColumn.longNoteHitTimes[noteColumn.longNoteTimeIndex];
                noteColumn.shrinkStartTime = mTimeElapsed;
                noteColumn.longNoteTimeIndex++;
                note->mIsMoving = false;
                note->SetPosition(vec2(noteColumn.xPos, 1080 - 90 * (mReceptorSize / 100)));
                noteColumn.isKeyHeld = true; // Indicates the note is being held
            }

            if (noteColumn.hitDifference >= 0 && noteColumn.hitDifference <= 18.9) {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
            }
            else if (noteColumn.hitDifference > 18.9 && noteColumn.hitDifference <= 37.8) {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
            }
            else if (noteColumn.hitDifference > 37.8 && noteColumn.hitDifference <= 75.6) {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
            }
            else if (noteColumn.hitDifference > 75.6 && noteColumn.hitDifference <= 113.4) {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
            }
            else {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
            }
       }
    }
}

void Game::UpdateLongNoteState(NoteColumn& noteColumn) {
    if (noteColumn.isKeyHeld) {
        // Access the note body from the renderer
        auto& note = mSpriteRenderer.mNoteBuffer[mCurrentGameState][
            noteColumn.noteName + "-long-note-body-" + to_string(noteColumn.releaseTimeIndex)
        ];
        float elapsedTimeSinceHit = mTimeElapsed - noteColumn.shrinkStartTime;
        float shrinkProgress = elapsedTimeSinceHit / noteColumn.shrinkDuration;

        shrinkProgress = std::clamp(shrinkProgress, 0.0f, 1.0f);

        // Calculate new height based on shrink progress
        float originalHeight = noteColumn.longNoteOriginalHeight;
        float newHeight = originalHeight * (1.0f - shrinkProgress);

        // Update the size of the note body
        if(note!=nullptr)
            note->SetSize(vec2(note->GetSize().x, newHeight));
    }
}


void Game::HandleHitRegistration(SDL_Event& event)
{
    if (SDL_GetKeyName(event.key.keysym.sym) == mLeftKeybind &&!event.key.repeat)
    {
        RegisterHit(mNoteColumns[0]);
    }
    if (SDL_GetKeyName(event.key.keysym.sym) == mDownKeybind && !event.key.repeat)
    {	
        RegisterHit(mNoteColumns[1]);
    }
    if (SDL_GetKeyName(event.key.keysym.sym) == mUpKeybind && !event.key.repeat)
    {
        RegisterHit(mNoteColumns[2]);
    }
    if (SDL_GetKeyName(event.key.keysym.sym) == mRightKeybind && !event.key.repeat)
    {
        RegisterHit(mNoteColumns[3]);
    }
}

void Game::HandleHitRelease(SDL_Event& event)
{
    if (SDL_GetKeyName(event.key.keysym.sym) == mLeftKeybind)
    {
        HandleLongNoteRelease(mNoteColumns[0]);
    }
    if (SDL_GetKeyName(event.key.keysym.sym) == mDownKeybind)
    {
        HandleLongNoteRelease(mNoteColumns[1]);
    }
    if (SDL_GetKeyName(event.key.keysym.sym) == mUpKeybind)
    {
        HandleLongNoteRelease(mNoteColumns[2]);
    }
    if (SDL_GetKeyName(event.key.keysym.sym) == mRightKeybind)
    {
        HandleLongNoteRelease(mNoteColumns[3]);
    }
}

void Game::HandleLongNoteRelease(NoteColumn& noteColumn)
{
    if (noteColumn.isKeyHeld && noteColumn.releaseTimeIndex < noteColumn.releaseTimes.size())
    {
        noteColumn.isKeyHeld = false;
        noteColumn.releaseTime = mTimeElapsed;
        noteColumn.releaseDifference = abs(noteColumn.releaseTime -
            noteColumn.releaseTimes[noteColumn.releaseTimeIndex]);
        mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase(
            noteColumn.noteName + "-long-note-body-" + to_string(noteColumn.releaseTimeIndex));
        if ( noteColumn.releaseDifference <= 180)
        {
            noteColumn.releaseTimeIndex++;
            if (noteColumn.hitDifference >= 0 && noteColumn.hitDifference <= 18.9) {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
            }
            else if (noteColumn.hitDifference > 18.9 && noteColumn.hitDifference <= 37.8) {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
            }
            else if (noteColumn.hitDifference > 37.8 && noteColumn.hitDifference <= 75.6) {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
            }
            else if (noteColumn.hitDifference > 75.6 && noteColumn.hitDifference <= 113.4) {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
            }
            else {
                GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
                    ->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
            }
        }
    }
}

void Game::HandleMissedHitRegistration()
{
    for (auto& noteColumn : mNoteColumns)
    {
        if (noteColumn.noteTimeIndex < noteColumn.hitTimes.size() &&
            mTimeElapsed > noteColumn.hitTimes[noteColumn.noteTimeIndex] + 180)
        {
            noteColumn.noteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
        if (noteColumn.longNoteTimeIndex < noteColumn.longNoteHitTimes.size() &&
            mTimeElapsed > noteColumn.longNoteHitTimes[noteColumn.longNoteTimeIndex] + 180)
        {
            noteColumn.longNoteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        } 
        if (noteColumn.releaseTimeIndex < noteColumn.releaseTimes.size() &&
            mTimeElapsed > noteColumn.releaseTimes[noteColumn.releaseTimeIndex] + 180)
        {
            mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase(
                noteColumn.noteName + "-long-note-body-" + to_string(noteColumn.releaseTimeIndex));
            noteColumn.releaseTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }
}



