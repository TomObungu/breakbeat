#include "Game.hpp"

void Game::LoadBackgroundImage()
{
    // Convert file extension to lowercase for case-insensitive comparison
    std::string extension = fs::path(mCurrentChartImageFile).extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // Check if the file is PNG or JPG and enable alpha accordingly
    bool useAlpha = extension == ".png";

    Texture bgImage = ResourceManager::loadTextureFromFile((fs::current_path().string() + "\\" + mCurrentChartImageFile).c_str(), useAlpha);
    GetSprite(mCurrentGameState, "main-gameplay-background-image")->SetTexture(bgImage);
}

bool Game::ParseDifficultyFile() 
{
    // Open difficulty file
    ifstream difficultyFile(fs::current_path().string() + "\\" + mCurrentChartFile);
    if (!difficultyFile.is_open()) {
        cerr << "Error: Unable to open difficulty file: " << mCurrentChartFile << '\n';
        return false;
    }

    // Store the line of the file being as a string object
    string line;
    // The regular expression for the column and the column type
    regex columnRegex(R"(^(\d+)\s+Column\s+(Hit|Long Note|Release)\s+Times:)");
    // The timing regular expression
    regex numberRegex(R"(\d+)");

    int currentColumn = -1; // Tracks which column is being processed
    string currentType; // Tracks the type: "Hit", "Long Note", "Release"

    while (getline(difficultyFile, line)) {
        smatch match;

        // Check if the line starts a new note type (Hit, Long Note, Release) for a column
        if (regex_search(line, match, columnRegex)) {
            currentColumn = stoi(match[1]); // Extract the column number (0, 1, 2, 3)
            currentType = match[2]; // "Hit", "Long Note", "Release"
            continue; // Move to the next line
        }

        // If we are processing a known column, extract times
        if (currentColumn >= 1 && currentColumn <= 4) {
            std::sregex_iterator it(line.begin(), line.end(), numberRegex);
            std::sregex_iterator end;

            vector<float>* targetVector = nullptr;

            // Determine which vector to update based on type
            if (currentType == "Hit") {
                if (currentColumn == 1) targetVector = &firstColumn.hitTimes;
                else if (currentColumn == 2) targetVector = &secondColumn.hitTimes;
                else if (currentColumn == 3) targetVector = &thirdColumn.hitTimes;
                else if (currentColumn == 4) targetVector = &fourthColumn.hitTimes;
            }
            else if (currentType == "Long Note") {
                if (currentColumn == 1) targetVector = &firstColumn.longNoteHitTimes;
                else if (currentColumn == 2) targetVector = &secondColumn.longNoteHitTimes;
                else if (currentColumn == 3) targetVector = &thirdColumn.longNoteHitTimes;
                else if (currentColumn == 4) targetVector = &fourthColumn.longNoteHitTimes;
            }
            else if (currentType == "Release") {
                if (currentColumn == 1) targetVector = &firstColumn.releaseTimes;
                else if (currentColumn == 2) targetVector = &secondColumn.releaseTimes;
                else if (currentColumn == 3) targetVector = &thirdColumn.releaseTimes;
                else if (currentColumn == 4) targetVector = &fourthColumn.releaseTimes;
            }

            // If we have a valid vector, populate it with parsed times
            if (targetVector) {
                for (; it != end; ++it) {
                    targetVector->push_back(std::stof(it->str()));
                }
            }
        }
    }
    mNoteColumns = { firstColumn,secondColumn,thirdColumn,fourthColumn };
    difficultyFile.close();
    return true;
}

void Game::InitializeMainGameplay()
{
    // Load the background image
    // Stop all the sounds (assuming transitioning from the chart selection)
    mSoundEngine->stopAllSounds();
    LoadBackgroundImage();
    GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("nil"));
    // Determine the size of the receptor based on the user's receptor size preference
    vec2 receptorSize = vec2(192.000 * (mReceptorSize / 100.0f), 180 * (mReceptorSize / 100.0f));

    // Ensure each sprite is fully brightened
    for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[mCurrentGameState])
    {
        if (sprite != nullptr)
            sprite->SetColor(vec3(1));
    }

    // Determine the size of the left most receptor 
    GetSprite(mCurrentGameState, "main-gameplay-left-note-receptor")->SetSize(receptorSize);
    // Offset the position of the receptor to the right based on the size of the receptor
    GetSprite(mCurrentGameState, "main-gameplay-left-note-receptor")->SetPosition(vec2(581.936, ((mReceptorSize / 100.0f) * -180) + 1080));
    GetSprite(mCurrentGameState, "z-main-gameplay-down-note-receptor")->SetSize(receptorSize);
    // OFfset the position of the rectpor to right plus an additional extra offest based on the spacing between each receptor
    GetSprite(mCurrentGameState, "z-main-gameplay-down-note-receptor")->SetPosition(vec2(((mReceptorSize / 100.0f) - 1) * 183.487 + 765.423, ((mReceptorSize / 100) * -180) + 1080));
    GetSprite(mCurrentGameState, "main-gameplay-up-note-receptor")->SetSize(receptorSize);
    GetSprite(mCurrentGameState, "main-gameplay-up-note-receptor")->SetPosition(vec2(((mReceptorSize / 100.0f) - 1) * 366.974 + 949.361, ((mReceptorSize / 100) * -180) + 1080));
    GetSprite(mCurrentGameState, "main-gameplay-right-note-receptor")->SetSize(receptorSize);
    GetSprite(mCurrentGameState, "main-gameplay-right-note-receptor")->SetPosition(vec2(((mReceptorSize / 100.0f) - 1) * 550.461 + 1138.061, ((mReceptorSize / 100) * -180) + 1080));
    // Multipy the size of the notefield based on the size of the receptors
    GetSprite(mCurrentGameState, "main-gameplay-gameplay-vsrg-column")->SetSize(vec2(755.998 * (mReceptorSize / 100.0f), 1080));
    // Set the position of the life bar to the right based on the size of the notefield
    GetSprite(mCurrentGameState, "main-gameplay-life-bar-handle")->SetPosition(vec2(575.321 + GetSprite(mCurrentGameState, "main-gameplay-gameplay-vsrg-column")->GetSize().x, 477.547));
    GetSprite(mCurrentGameState, "main-gameplay-life-bar")->SetSize(vec2(17.158, -594.710));
    GetSprite(mCurrentGameState, "main-gameplay-life-bar")->SetPosition(vec2(579.121 + GetSprite(mCurrentGameState, "main-gameplay-gameplay-vsrg-column")->GetSize().x, 1080));
    // Set the position of the judgement text to the center of the notefield.
    GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetPosition(vec2(579.121 + (GetSprite(mCurrentGameState, "main-gameplay-gameplay-vsrg-column")->GetSize().x / 2.0f) -
        (GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->GetSize().x / 2), 481.407));
    // Set the position song name and time elapsed text to the either side of the top of the notefield
    GetText(mCurrentGameState, "gameplay-song-name")->UpdateText(mCurrentSongName + format("[{}]", mCurrentSongDifficulty));
    GetText(mCurrentGameState, "gameplay-time-elapsed")->SetPosition(vec2(579.121 + GetSprite(mCurrentGameState, "main-gameplay-gameplay-vsrg-column")->GetSize().x * .70, 8.904));
    
    ParseDifficultyFile();
    
    PreloadAudio();

    mTimeTakenToFall = (1080 / mScrollSpeed) * 1000; // Time taken to fall in milliseconds

    for (unsigned i = 0; i < 4; i++)
    {
        mNoteColumns[i].xPos = i > 0 ? 581.936 + (i * 183.944) + ((mReceptorSize / 100.0f) - 1) * (i * 183.487) : 581.936;
    } 
    for (unsigned i = 0; i < 4; i++)
    {
        for (auto& time : mNoteColumns[i].hitTimes)
        {
            time += 100 / mReceptorSize * 180 / mScrollSpeed * 1000;
        }
        for (auto& time : mNoteColumns[i].longNoteHitTimes)
        {
            time += 100 / mReceptorSize * 180 / mScrollSpeed * 1000;
        }
        for (auto& time : mNoteColumns[i].releaseTimes)
        {
            time += 100 / mReceptorSize * 180 / mScrollSpeed * 1000;
        }
    }
    for (unsigned i = 0; i < 4; i++)
    {
        for (auto& time : mNoteColumns[i].hitTimes)
        {
            mNoteColumns[i].renderTimes.push_back(time - mTimeTakenToFall);
        }
        for (auto& time : mNoteColumns[i].longNoteHitTimes)
        {
            mNoteColumns[i].longNoteRenderTimes.push_back(time - mTimeTakenToFall);
        }
    }

    // Find the smallest negative value in renderTimes
    mNegativeOffset = 0.0f;
    for (unsigned i = 0; i < 4; i++)
    {
        for (float renderTime : mNoteColumns[i].renderTimes) {
            if (renderTime < 0) {
                mNegativeOffset = std::min(mNegativeOffset, renderTime); // Smallest (largest magnitude) negative value
            }
        }
        for (float renderTime : mNoteColumns[i].longNoteRenderTimes) {
            if (renderTime < 0) {
                mNegativeOffset = std::min(mNegativeOffset, renderTime); // Smallest (largest magnitude) negative value
            }
        }
    }
    mDelayStartTime = SDL_GetTicks();
}

void Game::PreloadAudio()
{
    // Load the sound into memory
    mSongSource = mSoundEngine->addSoundSourceFromFile(
        mCurrentChartAudioFile.c_str(),
        ESM_AUTO_DETECT, // Automatically detects format
        true             // Forces the sound to stay in memory
    );
    
    mSongSource = mSoundEngine->getSoundSource(mCurrentChartAudioFile.c_str());
    mCurrentSongDuration = mSongSource->getPlayLength();
}

void Game::StartSongWithAdjustedTiming()
{
    float timeElapsed = SDL_GetTicks() - mDelayStartTime;
    mTimeElapsed = (mNegativeOffset - mTimeTakenToFall) + timeElapsed;


    if (mTimeElapsed < 0) {
        RenderNotes(); // Keep rendering notes until the song starts
    }


    // When the song starts, play the preloaded sound (NO LAG!)
    if (!mSongPlaying && mTimeElapsed >= 0) {
        mSongStartTime = SDL_GetTicks();
        mSoundEngine->play2D(mSongSource, false); // No loading delay!);
        mSongPlaying = true;
    }
}


void Game::UpdateGameplayState()
{
    // Handle all necessary game logic updates
    RenderNotes();
    UpdateGameplayStatisticsText();
    HandleMissedHitRegistration();
    UpdateHealthBar();
    for (auto& noteColumn : mNoteColumns)
    {
        UpdateLongNoteState(noteColumn);
    }
}

void Game::HandleMainGameplay()
{
    if (!mSongPlaying) 
    {
        StartSongWithAdjustedTiming();
        // Ensure notes are synced before song starts
    }
    if(mSongPlaying)
    {
        // Update the time elapsed
        mTimeElapsed = SDL_GetTicks() - mSongStartTime;

        // Update the UI text to display minutes and seconds
        int minutes = static_cast<int>(mTimeElapsed / 60000); // Convert ms to minutes
        int seconds = (static_cast<int>(mTimeElapsed / 1000)) % 60; // Convert ms to seconds (mod 60)
        GetText(mCurrentGameState, "gameplay-time-elapsed")
            ->UpdateText("Time Elapsed : " + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds));

        // Update the gameplay state (handles rendering, hit registration, etc.)
        UpdateGameplayState();
    }
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
            mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase(noteColumn.noteName + '-' + to_string(noteColumn.noteTimeIndex));
            if (noteColumn.noteTimeIndex < noteColumn.hitTimes.size())
                noteColumn.noteTimeIndex++;
            mMaximumPossibleScore += 320;
            UpdateScore(noteColumn);
        }
    }
    if (noteColumn.longNoteTimeIndex < noteColumn.longNoteHitTimes.size())
    {
        noteColumn.hitTime= mTimeElapsed;
        noteColumn.hitDifference = noteColumn.hitTime- noteColumn.longNoteHitTimes[noteColumn.longNoteTimeIndex];

        if (noteColumn.hitDifference <= 180 && noteColumn.hitDifference > -45) { // Within hit window
            
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
                mMaximumPossibleScore += 320;
                noteColumn.isKeyHeld = true; // Indicates the note is being held
            }

            UpdateScoreLongNotes(noteColumn);
       }
    }
}

void Game::UpdateLongNoteState(NoteColumn& noteColumn) {
    if (noteColumn.isKeyHeld) {

        // Access the note body from the renderer
        auto& note = mSpriteRenderer.mNoteBuffer[mCurrentGameState][
            noteColumn.noteName + "-long-note-body-" + to_string(noteColumn.releaseTimeIndex)
        ];

        if (note != nullptr)
        {
            if (note->GetPosition().y >= 1080 - 90 * (mReceptorSize / 100))
                note->mIsMoving = false;
            note->SetPosition(vec2(noteColumn.xPos, 1080 - 90 * (mReceptorSize / 100)));
        }
        
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
            mMaximumPossibleScore += 320;
            UpdateScoreRelease(noteColumn);
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
            mMaximumPossibleScore += 320;
            mMissCount++;
            mHealth -= 10;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
        if (noteColumn.longNoteTimeIndex < noteColumn.longNoteHitTimes.size() &&
            mTimeElapsed > noteColumn.longNoteHitTimes[noteColumn.longNoteTimeIndex] + 180)
        {
            noteColumn.longNoteTimeIndex++;
            mMaximumPossibleScore += 320;
            mMissCount++;
            mHealth -= 10;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        } 
        if (noteColumn.releaseTimeIndex < noteColumn.releaseTimes.size() &&
            mTimeElapsed > noteColumn.releaseTimes[noteColumn.releaseTimeIndex] + 180)
        {
            mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase(
                noteColumn.noteName + "-long-note-body-" + to_string(noteColumn.releaseTimeIndex));
            noteColumn.releaseTimeIndex++;
            mMaximumPossibleScore += 320;
            mMissCount++;
            mHealth -= 10;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }
}

void Game::UpdateGameplayStatisticsText()
{
    mAccuracy = (mScore == 0.0f && mMaximumPossibleScore == 0.0f) ? 0 : mScore / mMaximumPossibleScore * 100;
    GetText(mCurrentGameState, "gameplay-score")->UpdateText("Score : "+format("{}",mScore));
    GetText(mCurrentGameState, "gameplay-accuracy")->UpdateText("Accuracy : "+format("{:.2f}", mAccuracy));
    GetText(mCurrentGameState, "gameplay-flawless-count")->UpdateText("Flawless : "+format("{}",mFlawlessCount));
    GetText(mCurrentGameState, "gameplay-perfect-count")->UpdateText("Perfect  : "+format("{}",mPerfectCount));
    GetText(mCurrentGameState, "gameplay-great-count")->UpdateText("Great : "+format("{}",mGreatCount));
    GetText(mCurrentGameState, "gameplay-good-count")->UpdateText("Good : "+format("{}",mGoodCount));
    GetText(mCurrentGameState, "gameplay-bad-count")->UpdateText("Bad : "+format("{}",mBadCount));
    GetText(mCurrentGameState, "gameplay-miss-count")->UpdateText("Miss : "+format("{}",mMissCount));
    
    if(mAccuracy == 100)
        GetText(mCurrentGameState, "gameplay-current-grade")->UpdateText("Current Grade : SS");
    else if (mAccuracy > 95)
        GetText(mCurrentGameState, "gameplay-current-grade")->UpdateText("Current Grade : S"); 
    else if (mAccuracy <= 95 && mAccuracy > 90)
        GetText(mCurrentGameState, "gameplay-current-grade")->UpdateText("Current Grade : A");   
    else if (mAccuracy <= 90 && mAccuracy > 80)
        GetText(mCurrentGameState, "gameplay-current-grade")->UpdateText("Current Grade : B");    
    else if (mAccuracy <= 80 && mAccuracy > 70)
        GetText(mCurrentGameState, "gameplay-current-grade")->UpdateText("Current Grade : C");
    else
        GetText(mCurrentGameState, "gameplay-current-grade")->UpdateText("Current Grade : D");
}

void Game::UpdateScore(NoteColumn& noteColumn)
{
    if (noteColumn.hitDifference >= 0 && noteColumn.hitDifference <= 18.9) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
        mScore += 320;
        mHealth += mHealth < 100 ? 10 * 320 / 320 : 0;
        mFlawlessCount++;
    }
    else if (noteColumn.hitDifference > 18.9 && noteColumn.hitDifference <= 37.8) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
        mScore += 300;
        mHealth += mHealth < 100 ? 10 * 300 / 320 : 0;
        mPerfectCount++;
    }
    else if (noteColumn.hitDifference > 37.8 && noteColumn.hitDifference <= 75.6) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
        mScore += 200;
        mHealth += mHealth < 100 ? 10 * 200/320 : 0;
        mGreatCount++;
    }
    else if (noteColumn.hitDifference > 75.6 && noteColumn.hitDifference <= 113.4) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
        mScore += 100;
        mHealth += mHealth < 100 ? 10 * 100/200 : 0;
        mGoodCount++;
    }
    else {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
        mScore += 50;
        mHealth += mHealth < 100 ? 10 * 50 / 320: 0;
        mBadCount++;
    }
}

void Game::UpdateScoreLongNotes(NoteColumn& noteColumn)
{
    if (noteColumn.longNoteHitDifference >= 0 && noteColumn.longNoteHitDifference <= 18.9) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
        mScore += 320;
        mHealth += mHealth < 100 ? 10 * 320 / 320 : 0;
        mFlawlessCount++;
    }
    else if (noteColumn.longNoteHitDifference > 18.9 && noteColumn.longNoteHitDifference <= 37.8) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
        mScore += 300;
        mHealth += mHealth < 100 ? 10 * 300 / 320 : 0;
        mPerfectCount++;
    }
    else if (noteColumn.longNoteHitDifference > 37.8 && noteColumn.longNoteHitDifference <= 75.6) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
        mScore += 200;
        mHealth += mHealth < 100 ? 10 * 200 / 320 : 0;
        mGreatCount++;
    }
    else if (noteColumn.longNoteHitDifference > 75.6 && noteColumn.longNoteHitDifference <= 113.4) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
        mScore += 100;
        mHealth += mHealth < 100 ? 10 * 100 / 200 : 0;
        mGoodCount++;
    }
    else {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
        mScore += 50;
        mHealth += mHealth < 100 ? 10 * 50 / 320 : 0;
        mBadCount++;
    }
}

void Game::UpdateScoreRelease(NoteColumn& noteColumn)
{
    if (noteColumn.releaseDifference >= 0 && noteColumn.releaseDifference <= 18.9) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
        mScore += 320;
        mHealth += mHealth < 100 ? 10 * 320 / 320 : 0;
        mFlawlessCount++;
    }
    else if (noteColumn.releaseDifference > 18.9 && noteColumn.releaseDifference <= 37.8) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
        mScore += 300;
        mHealth += mHealth < 100 ? 10 * 300 / 320 : 0;
        mPerfectCount++;
    }
    else if (noteColumn.releaseDifference > 37.8 && noteColumn.releaseDifference <= 75.6) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
        mScore += 200;
        mHealth += mHealth < 100 ? 10 * 200 / 320 : 0;
        mGreatCount++;
    }
    else if (noteColumn.releaseDifference > 75.6 && noteColumn.releaseDifference <= 113.4) {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
        mScore += 100;
        mHealth += mHealth < 100 ? 10 * 100 / 200 : 0;
        mGoodCount++;
    }
    else {
        GetSprite(mCurrentGameState, "main-gameplay-judgement-text")
            ->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
        mScore += 50;
        mHealth += mHealth < 100 ? 10 * 50 / 320 : 0;
        mBadCount++;
    }
}

void Game::UpdateHealthBar()
{
    mHealth = std::clamp(mHealth, 0, 100);
    GetSprite(mCurrentGameState, "main-gameplay-life-bar")->SetSize(vec2(17.158, -594.710 * (mHealth / 100.0f)));
}


