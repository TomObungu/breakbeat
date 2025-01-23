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

    // Reset song start time
   
    combineAndSortHitTimes(firstColumnCombinedHitTimes, firstColumnNoteHitTimes, firstColumnLongNoteHitTimes);
    combineAndSortHitTimes(secondColumnCombinedHitTimes, secondColumnNoteHitTimes, secondColumnLongNoteHitTimes);
    combineAndSortHitTimes(thirdColumnCombinedHitTimes, thirdColumnNoteHitTimes, thirdColumnLongNoteHitTimes);
    combineAndSortHitTimes(fourthColumnCombinedHitTimes, fourthColumnNoteHitTimes, fourthColumnLongNoteHitTimes);   

    float totalDistance = 1080; // Adjusted for note height and receptor size
    float timeTakenToFall = (totalDistance / mScrollSpeed) * 1000; // Convert to milliseconds
    
    // Calculate render times based on the sorted hit times
    for (auto& time : firstColumnCombinedHitTimes) {
        firstColumnNoteRenderTimes.push_back((time - timeTakenToFall));
    }
    for (auto& time : secondColumnCombinedHitTimes) {
        secondColumnNoteRenderTimes.push_back((time - timeTakenToFall));
    }
    for (auto& time : thirdColumnCombinedHitTimes) {
        thirdColumnNoteRenderTimes.push_back((time - timeTakenToFall));
    }
    for (auto& time : fourthColumnCombinedHitTimes) {
        fourthColumnNoteRenderTimes.push_back((time - timeTakenToFall));
    }  

    for (auto& time : firstColumnLongNoteHitTimes) {
        firstColumnLongNoteRenderTimes.push_back((time - timeTakenToFall));
    }
    for (auto& time : secondColumnLongNoteHitTimes) {
        secondColumnLongNoteRenderTimes.push_back((time - timeTakenToFall));
    }
    for (auto& time : thirdColumnLongNoteHitTimes) {
        thirdColumnLongNoteRenderTimes.push_back((time - timeTakenToFall));
    }
    for (auto& time : fourthColumnLongNoteHitTimes) {
        fourthColumnLongNoteRenderTimes.push_back((time - timeTakenToFall));
    }
    // Initialize the note rendering system

    mSoundEngine->play2D("C:\\Users\\deeza\\AppData\\Local\\osu!\\Songs\\828129 Sharkey & Arkitech - Quadraphinix\\Quadraphinix_0 0.750x.mp3", false);
    mSongStartTime = SDL_GetTicks();
    mSongPlaying = true;
}

void Game::HandleMainGameplay()
{
    // Update the time elapsed
    mTimeElapsed = SDL_GetTicks() - mSongStartTime;

    GetText(mCurrentGameState, "gameplay-time-elapsed")->UpdateText(to_string(mTimeElapsed));

    // Render notes
    RenderNotes();

    HandleMissedHitRegistration();
}

// Function to combine and sort hit times
void Game::combineAndSortHitTimes(std::vector<float>& combinedHitTimes, const std::vector<float>& noteHitTimes, const std::vector<float>& longNoteHitTimes)
{
    // Combine the hit times
    combinedHitTimes.insert(combinedHitTimes.end(), noteHitTimes.begin(), noteHitTimes.end());
    combinedHitTimes.insert(combinedHitTimes.end(), longNoteHitTimes.begin(), longNoteHitTimes.end());

    // Sort the combined hit times
    std::sort(combinedHitTimes.begin(), combinedHitTimes.end());
}

// Main logic

void Game::RenderNotes()
{
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

    if (secondColumnNextLongNoteRenderIndex < secondColumnLongNoteRenderTimes.size() &&
        mTimeElapsed >= (secondColumnLongNoteRenderTimes[secondColumnNextLongNoteRenderIndex]))
    {
        const string& noteName = "main-gameplay-down-long-note-body-" + to_string(secondColumnNextLongNoteRenderIndex);
        const float& offset = ((secondColumnNoteReleaseTimes[secondColumnNextReleaseTimeIndex] -
            secondColumnLongNoteRenderTimes[secondColumnNextLongNoteRenderIndex]) * mScrollSpeed / 1000);

        mSpriteRenderer.CreateNote(
            GameState::MAIN_GAMEPLAY,
            noteName,
            ResourceManager::GetTexture("main-gameplay-hold-note-body"),
            vec2(((mReceptorSize / 100.0f) - 1) * 183.487 + 765.423, -180 * (mReceptorSize / 100)), // Start position at the top
            vec2(192.000 * (mReceptorSize / 100), (secondColumnNoteReleaseTimes[secondColumnNextReleaseTimeIndex] -
                secondColumnLongNoteRenderTimes[secondColumnNextLongNoteRenderIndex] * mScrollSpeed / 1000)),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );

        secondColumnNextLongNoteRenderIndex++;
        secondColumnNextReleaseTimeIndex++;

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

void Game::RegisterHit(const vector<float>& noteHitTimes, float& hitTime, float& hitDifference, float& noteIndex, bool& hitNoteBoolean, const string& noteName)
{
    hitTime = mTimeElapsed;
    hitDifference = abs(hitTime - noteHitTimes[noteIndex]);
    if (hitDifference <= 180)
    {
        hitNoteBoolean = true;
        mSpriteRenderer.mNoteBuffer[mCurrentGameState].erase(noteName + to_string(noteIndex));
        if (noteIndex < noteHitTimes.size())
            noteIndex++;
        if (hitDifference >= 0 && hitDifference <= 18.9)
        {
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("flawless-judgement-text"));
        }
        else if (hitDifference > 18.9 && hitDifference <= 37.8)
        {
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("perfect-judgement-text"));
        }
        else if (hitDifference > 37.8 && hitDifference<= 75.6)
        {
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("great-judgement-text"));
        }
        if (hitDifference > 75.6 && hitDifference <= 113.4)
        {
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("good-judgement-text"));
        }
        if (hitDifference > 113.4 && hitDifference <= 180)
        {
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("bad-judgement-text"));
        }
    }
}


void Game::HandleHitRegistration(SDL_Event& event)
{
    HitNoteInFirstColumn = false;
    if (SDL_GetKeyName(event.key.keysym.sym) == mLeftKeybind)
    {
		RegisterHit(firstColumnCombinedHitTimes, firstColumnHitTime, firstColumnHitDifference, firstColumnNextNoteTimeIndex, HitNoteInFirstColumn, "main-gameplay-left-note-");
    }
    HitNoteInSecondColumn = false;
	if (SDL_GetKeyName(event.key.keysym.sym) == mDownKeybind)
	{
		RegisterHit(secondColumnCombinedHitTimes, secondColumnHitTime, secondColumnHitDifference, secondColumnNextNoteTimeIndex, HitNoteInSecondColumn, "main-gameplay-down-note-");
	}
    HitNoteInThirdColumn = false;
	if (SDL_GetKeyName(event.key.keysym.sym) == mUpKeybind)
	{
		RegisterHit(thirdColumnCombinedHitTimes, thirdColumnHitTime, thirdColumnHitDifference, thirdColumnNextNoteTimeIndex, HitNoteInThirdColumn, "main-gameplay-up-note-");
    }
    HitNoteInFourthColumn = false;
	if (SDL_GetKeyName(event.key.keysym.sym) == mRightKeybind)
	{
		RegisterHit(fourthColumnCombinedHitTimes, fourthColumnHitTime, fourthColumnHitDifference, fourthColumnNextNoteTimeIndex, HitNoteInFourthColumn, "main-gameplay-right-note-");
	}
}

void Game::HandleMissedHitRegistration()
{

    if (firstColumnNextNoteTimeIndex < firstColumnCombinedHitTimes.size())
    {
        if (mTimeElapsed > firstColumnCombinedHitTimes[firstColumnNextNoteTimeIndex] + 180)
        {
            firstColumnNextNoteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }    
    if (secondColumnNextNoteTimeIndex < secondColumnCombinedHitTimes.size())
    {
        if (mTimeElapsed > secondColumnCombinedHitTimes[secondColumnNextNoteTimeIndex] + 180)
        {
            secondColumnNextNoteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }    
    if (thirdColumnNextNoteTimeIndex < thirdColumnCombinedHitTimes.size())
    {
        if (mTimeElapsed > thirdColumnCombinedHitTimes[thirdColumnNextNoteTimeIndex] + 180)
        {
            thirdColumnNextNoteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }    
    if (fourthColumnNextNoteTimeIndex < fourthColumnCombinedHitTimes.size())
    {
        if (mTimeElapsed > fourthColumnCombinedHitTimes[fourthColumnNextNoteTimeIndex] + 180)
        {
            fourthColumnNextNoteTimeIndex++;
            GetSprite(mCurrentGameState, "main-gameplay-judgement-text")->SetTexture(ResourceManager::GetTexture("miss-judgement-text"));
        }
    }
}



