#include "Game.hpp"#

void Game::InitializeChartEditor()
{
	LoadBackgroundImage();
	ParseDifficultyFile();
	PreloadAudio();
	for (unsigned i = 0; i < 4; i++)
	{
		mNoteColumns[i].xPos = i > 0 ? 1158.573 + (i * 192.805) : 1158.573;
    }
    mPreviewWindowSize = 1080 / mTimelineZoom * 1000;
    RenderChartEditor();
    UpdateNotePreviewBuffer();
    UpdateBeatSnapBars();
}

void Game::RenderChartEditor()
{
    // Ensure we have notes to render
    if (mNoteColumns.empty()) return;

    // Find the earliest note timing across all columns
    if (mFirstBeatTime == -1) // Only calculate once
    {
        mFirstBeatTime = FindEarliestNoteTime();
        mTimelinePreview = mFirstBeatTime; // Start at first note timing
    }

    // Compute beat interval
    mBeatInterval = 1000.0f / (stof(mCurrentSongBPM) / 60.0f) / (float) mBeatSnap;

    // Loop through all note columns
    for (unsigned col = 0; col < mNoteColumns.size(); col++)
    {
        for (float i = 0; i < mNoteColumns[col].hitTimes.size(); i++)
        {
            float noteTime = mNoteColumns[col].hitTimes[i];

            // Calculate Y position relative to mTimeLinePreview
            float yOffset = 900 - ((noteTime - mTimelinePreview) * mTimelineZoom) / 1000.0f;

            // Only render if the note is within visible range

            RenderNote(mNoteColumns[col], yOffset); // Render the note

        }
    }
}

void Game::RefreshChartEditorNoteBuffer()
{
    // Loop through all note columns
    for (unsigned col = 0; col < mNoteColumns.size(); col++)
    {
        mNoteColumns[col].releaseTimeRenderTimeIndex = 0;
        for (float i = 0; i < mNoteColumns[col].hitTimes.size(); i++)
        {
            float noteTime = mNoteColumns[col].hitTimes[i];

            // Calculate Y position relative to mTimeLinePreview
            float yOffset = 900 - ((noteTime - mTimelinePreview) * mTimelineZoom) / 1000.0f;

            // Only render if the note is within visible range

            RenderNote(mNoteColumns[col], yOffset); // Render the note

        }
    }
}

// Function to find the first note time in all columns
float Game::FindEarliestNoteTime()
{
    float earliestTime = FLT_MAX;
    for (const auto& column : mNoteColumns)
    {
        if (!column.hitTimes.empty())
        {
            earliestTime = min(earliestTime, column.hitTimes.front());
        }
    }
    return earliestTime;
}

void Game::RenderNote(NoteColumn& noteColumn, float yOffset)
{
    if (noteColumn.renderTimeIndex < noteColumn.hitTimes.size() &&
        mTimelinePreview <= (noteColumn.hitTimes[noteColumn.renderTimeIndex]))
    {
        mSpriteRenderer.CreateNote(
            mCurrentGameState,
            noteColumn.noteName + '-' + to_string(noteColumn.renderTimeIndex),
            ResourceManager::GetTexture(noteColumn.noteName),
            vec2(noteColumn.xPos, yOffset),
            vec2(192.000, 180),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );
        noteColumn.renderTimeIndex++;
    }
}

void Game::UpdateNotePreviewBuffer()
{
    mSpriteRenderer.mNotePreviewBuffer.clear(); // Clear previous buffer

    float previewEndTime = mTimelinePreview + mPreviewWindowSize;

    for (unsigned col = 0; col < mNoteColumns.size(); col++)
    {
        for (float i = 0; i < mNoteColumns[col].hitTimes.size(); ++i)
        {
            if (mNoteColumns[col].hitTimes[i] >= mTimelinePreview && mNoteColumns[col].hitTimes[i] <= previewEndTime)
            {
                mSpriteRenderer.mNotePreviewBuffer[mCurrentGameState]
                    [mNoteColumns[col].noteName + '-' + to_string(i)] = 
                        mSpriteRenderer.mNoteBuffer[mCurrentGameState][mNoteColumns[col].noteName 
                            + '-' + to_string(i)]; // Store visible notes
            }
        }
    }
}

void Game::UpdateNotePositions()
{
    float previewEndTime = mTimelinePreview + mPreviewWindowSize;

    // Iterate through all note columns
    for (unsigned col = 0; col < mNoteColumns.size(); col++)
    {
        for (float i = 0; i < mNoteColumns[col].hitTimes.size(); i++)
        {
            float noteTime = mNoteColumns[col].hitTimes[i];

            // Only update the position of notes in the preview range
            if (noteTime >= mTimelinePreview && noteTime <= previewEndTime)
            {
                string noteKey = mNoteColumns[col].noteName + '-' + std::to_string(i);

                // Check if the note exists in the preview buffer
                if (mSpriteRenderer.mNotePreviewBuffer[mCurrentGameState].find(noteKey) 
                    != mSpriteRenderer.mNotePreviewBuffer[mCurrentGameState].end())
                {
                    // Calculate the new Y position based on scrolling
                    float yOffset = 900 - ((noteTime - mTimelinePreview) * mTimelineZoom) / 1000.0f;

                    // Update the note's position in the preview buffer
                    mSpriteRenderer.mNotePreviewBuffer[mCurrentGameState][noteKey]
                        ->SetPosition(
                            vec2(mSpriteRenderer.mNotePreviewBuffer[mCurrentGameState][noteKey]->GetPosition().x,yOffset));
                }
            }
        }
    }
}

void Game::UpdateBeatSnapBars()
{
    int barCount = std::ceil(mPreviewWindowSize / mBeatInterval);
    for (unsigned i = 1; i < barCount + 1; i++)
    {
        mSpriteRenderer.CreateBar(
            mCurrentGameState,
            "beatsnap-bar-" + to_string(mTimelinePreview+i*mBeatInterval),
            ResourceManager::GetTexture("chart-editing-beat-snap-bar"),
            vec2(1158.241, (i+0.5)  * mBeatInterval / 1000 * mTimelineZoom ),
            vec2(761.759, 4.000),
            0.0f,
            vec3(1.0f),
            ResourceManager::GetShader("default"),
            false
        );
    }
}




