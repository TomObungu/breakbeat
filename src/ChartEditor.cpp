#include "Game.hpp"

void Game::InitializeChartEditor()
{
	LoadBackgroundImage();
    ClearGameplayBuffers();
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
    PreloadAudio();
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
    mSpriteRenderer.mBarBuffer.clear();
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

bool Game::EditDifficultyFile()
{
    // Open the difficulty file
    std::ifstream difficultyFile(fs::current_path().string() + "\\" + mCurrentChartFile);
    if (!difficultyFile.is_open()) {
        std::cerr << "Error: Unable to open difficulty file for editing." << std::endl;
        return false;
    }

    // Data structure to hold parsed chart data
    struct ChartData {
        std::vector<float> hitTimes;
        std::vector<float> longNoteHitTimes;
        std::vector<float> releaseTimes;
    };

    ChartData columnData[4]; // One for each column (0-3)

    // Regular expressions for parsing
    std::string line;
    std::regex columnRegex(R"(^(\d+)\s+Column\s+(Hit|Long Note|Release)\s+Times:)");
    std::regex numberRegex(R"(\d+)");

    // Store metadata
    std::vector<std::string> metadataLines;

    int currentColumn = -1; // Tracks which column is being processed
    std::string currentType; // Tracks the type: "Hit", "Long Note", "Release"

    // Read and parse the difficulty file
    while (std::getline(difficultyFile, line)) {
        std::smatch match;

        // Check if the line starts a new note type (Hit, Long Note, Release) for a column
        if (std::regex_search(line, match, columnRegex)) {
            currentColumn = std::stoi(match[1]) - 1; // Convert column to 0-based index
            currentType = match[2]; // "Hit", "Long Note", "Release"
            continue;
        }

        // Check for metadata lines before column definitions
        if (currentColumn == -1) {
            metadataLines.push_back(line); // Store metadata line
            continue;
        }

        // If we are processing a known column, extract timing values
        if (currentColumn >= 0 && currentColumn < 4) {
            std::sregex_iterator it(line.begin(), line.end(), numberRegex);
            std::sregex_iterator end;

            // Populate the appropriate vector based on currentType
            if (currentType == "Hit") {
                for (; it != end; ++it) {
                    columnData[currentColumn].hitTimes.push_back(std::stof(it->str()));
                }
            }
            else if (currentType == "Long Note") {
                for (; it != end; ++it) {
                    columnData[currentColumn].longNoteHitTimes.push_back(std::stof(it->str()));
                }
            }
            else if (currentType == "Release") {
                for (; it != end; ++it) {
                    columnData[currentColumn].releaseTimes.push_back(std::stof(it->str()));
                }
            }
        }
    }

    difficultyFile.close(); // Close the input file

    // Update the chart data with the current state of mNoteColumns
    for (int col = 0; col < 4; ++col) {
        columnData[col].hitTimes = mNoteColumns[col].hitTimes;
        // You can similarly update longNoteHitTimes and releaseTimes if those are edited
    }

    // Write the updated chart data back to the difficulty file
    std::ofstream outputDifficultyFile(fs::current_path().string() + "\\" + mCurrentChartFile, std::ios::trunc);
    if (!outputDifficultyFile.is_open()) {
        std::cerr << "Error: Unable to open difficulty file for writing." << std::endl;
        return false;
    }

    // Write metadata back to the file
    for (const auto& metadataLine : metadataLines) {
        outputDifficultyFile << metadataLine << "\n";
    }

    // Write updated chart data
    for (int col = 0; col < 4; ++col) {
        // Write Hit Times
        if (!columnData[col].hitTimes.empty()) {
            outputDifficultyFile << (col + 1) << " Column Hit Times:\n";
            for (float time : columnData[col].hitTimes) {
                outputDifficultyFile << static_cast<int>(time) << ",\n";
            }
            outputDifficultyFile << "\n";
        }

        // Write Long Note Hit Times
        if (!columnData[col].longNoteHitTimes.empty()) {
            outputDifficultyFile << (col + 1) << " Column Long Note Times:\n";
            for (float time : columnData[col].longNoteHitTimes) {
                outputDifficultyFile << static_cast<int>(time) << ",\n";
            }
            outputDifficultyFile << "\n";
        }

        // Write Release Times
        if (!columnData[col].releaseTimes.empty()) {
            outputDifficultyFile << (col + 1) << " Column Release Times:\n";
            for (float time : columnData[col].releaseTimes) {
                outputDifficultyFile << static_cast<int>(time) << ",\n";
            }
            outputDifficultyFile << "\n";
        }
    }

    outputDifficultyFile.close();
    std::cout << "Successfully updated the difficulty file while preserving metadata!" << std::endl;

    return true;
}