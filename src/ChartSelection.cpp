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
                if (text != nullptr && key != ("difficulty-select-box-text-1")
                    && key != ("difficulty-select-box-text-2")
                    && key != ("difficulty-select-box-text-3")
                    && key != ("difficulty-select-box-text-4"))
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
            textTable.erase("song-text-3");
            textTable.erase("artist-text-3");
            textTable.erase("song-text-4");
            textTable.erase("artist-text-4");
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
            mAddingSprites = false;
        }
    }
    else if (mShowNewDifficultyScreen)
    {
        if (!mTransitioningDark && !mAllDark)
        {
            mTransitioningDark = true;
            mAllLight = false;
            for (auto& [key, sprite] : table)
            {
                if (sprite != nullptr)
                    sprite->SetColor(vec3(0.5f));
            }
            for (auto& [key, text] : textTable)
            {
                if (text != nullptr && key != ("difficulty-select-box-text-1")
                    && key != ("difficulty-select-box-text-2")
                    && key != ("difficulty-select-box-text-3")
                    && key != ("difficulty-select-box-text-4"))
                    text->SetColor(vec3(0.5f));
            }
            mTransitioningDark = false;
            mAllDark = true;
        }
        if (!mAddingSprites && !mNewDifficultySpritesOnScreen)
        {
            if (table.contains("z-chart-editor-new-difficullty-user-interface-box") ||
                table.contains("zz-chart-editor-new-difficulty-user-interface-box-new-image") ||
                table.contains("zz-chart-editor-new-difficulty-create-button"))
            {
                mNewDifficultySpritesOnScreen = true;
            }
            mAddingSprites = true;
        }
        if (mAddingSprites && !mNewDifficultySpritesOnScreen)
        {
            table["z-chart-editor-new-difficullty-user-interface-box"] = GetDefaultSprite(mCurrentGameState, "z-chart-editor-new-difficullty-user-interface-box");
            table["zz-chart-editor-new-difficulty-user-interface-box-new-image"] = GetDefaultSprite(mCurrentGameState, "zz-chart-editor-new-difficulty-user-interface-box-new-image");
            table["zz-chart-editor-new-difficulty-create-button"] = GetDefaultSprite(mCurrentGameState, "zz-chart-editor-new-difficulty-create-button");
            textTable.erase("song-text-3");
            textTable.erase("artist-text-3");
            textTable.erase("song-text-4");
            textTable.erase("artist-text-4");
            textTable.erase("song-text-5");
            textTable.erase("artist-text-5");
            textTable["new-difficulty-screen-difficulty-name-text"] = GetDefaultText(mCurrentGameState, "new-difficulty-screen-difficulty-name-text");
            textTable["new-difficulty-screen-difficulty-name-text-box"] = GetDefaultText(mCurrentGameState, "new-difficulty-screen-difficulty-name-text-box");
            textTable["new-difficulty-screen-chart-image-text"] = GetDefaultText(mCurrentGameState, "new-difficulty-screen-chart-image-text");
            mAddingSprites = false;
        }
    }
    else if(removingSprites)
    {
        if(table.contains("z-chart-editor-new-chart-user-interface") ||
            table.contains("zz-chart-editor-new-chart-create-button") ||
            table.contains("zz-chart-editor-new-chart-user-interface-box-new-image") ||
            table.contains("z-chart-editor-new-difficullty-user-interface-box") ||
            table.contains("zz-chart-editor-new-difficulty-user-interface-box-new-image") ||
            table.contains("zz-chart-editor-new-difficulty-create-button") )
        {
            table.erase("z-chart-editor-new-chart-user-interface");
            table.erase("zz-chart-editor-new-chart-create-button");
            table.erase("zz-chart-editor-new-chart-user-interface-box-new-image");

            textTable.erase("new-chart-screen-song-name-text");
            textTable.erase("new-chart-screen-song-name-text-box");

            textTable.erase("new-chart-screen-artist-name-text");
            textTable.erase("new-chart-screen-artist-name-text-box");

            textTable.erase("new-chart-screen-difficulty-name-text");
            textTable.erase("new-chart-screen-difficulty-name-text-box");

            textTable.erase("new-chart-screen-song-bpm-text");
            textTable.erase("new-chart-screen-song-bpm-text-box");

            textTable.erase("new-chart-screen-chart-image-text");
            textTable.erase("new-chart-screen-chart-audio-text");
            
            mNewChartSpritesOnScreen = false;

            // Remove all new difficulty UI elements
            table.erase("z-chart-editor-new-difficullty-user-interface-box");
            table.erase("zz-chart-editor-new-difficulty-user-interface-box-new-image");
            table.erase("zz-chart-editor-new-difficulty-create-button");

            textTable.erase("new-difficulty-screen-difficulty-name-text");
            textTable.erase("new-difficulty-screen-difficulty-name-text-box");
            textTable.erase("new-difficulty-screen-chart-image-text");
       
            mNewDifficultySpritesOnScreen = false;

            // Restore the standard chart UI elements
            textTable["song-text-3"] = GetDefaultText(mCurrentGameState, "song-text-3");
            textTable["artist-text-3"] = GetDefaultText(mCurrentGameState, "artist-text-3");
            textTable["song-text-4"] = GetDefaultText(mCurrentGameState, "song-text-4");
            textTable["artist-text-4"] = GetDefaultText(mCurrentGameState, "artist-text-4");
            textTable["song-text-5"] = GetDefaultText(mCurrentGameState, "song-text-5");
            textTable["artist-text-5"] = GetDefaultText(mCurrentGameState, "artist-text-5");


            // Reload the charts from the directory
            GetCurrentChartDirectories();

            // Update the chart selection to reflect the current state
            UpdateChartSelection();
            removingSprites = true;
        }
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
                if (text != nullptr && key != ("difficulty-select-box-text-1")
                    && key != ("difficulty-select-box-text-2")
                    && key != ("difficulty-select-box-text-3")
                    && key != ("difficulty-select-box-text-4"))
                    text->SetColor(vec3(1.0f));
                else
                    text->SetColor(vec3(0.0f));
            }
            mTransitioningLight = false;
            mAllLight = true;
            mAllDark = false;
        }
    }
}

void Game::UpdateChartSelection()
{
    unsigned totalCharts = mAllCharts.size();

    // Ensure valid state when no charts are available
    if (totalCharts == 0)
    {
        mCurrentlyPreviewedCharts.fill("");
        for (unsigned i = 0; i < 7; ++i)
        {
            GetText(mCurrentGameState, "artist-text-" + to_string(i + 1))->UpdateText("NO SONG");
            GetText(mCurrentGameState, "song-text-" + to_string(i + 1))->UpdateText("NO ARTIST");
        }
        return;
    }

    // Calculate the end index based on the start index
    mChartPreviewEndIndex = (mChartPreviewStartIndex + 6) % totalCharts;

    // Update `mCurrentlyPreviewedCharts` based on start and end indices
    for (unsigned i = 0; i < 7; ++i)
    {
        unsigned currentIndex = (mChartPreviewStartIndex + i) % totalCharts;
        mCurrentlyPreviewedCharts[i] = mAllCharts[currentIndex];
    }

    regex chartName(R"(\s*-\s*(.+))");
    // Update the UI with artist and song names
    for (unsigned i = 0; i < 7; ++i)
    {
        const string& chartName = mCurrentlyPreviewedCharts[i];
        unsigned lastDelimiterPos = chartName.rfind('-'); // Find the last dash

        if (lastDelimiterPos != string::npos)
        {
            string artistName = chartName.substr(0, lastDelimiterPos);
            string songName = chartName.substr(lastDelimiterPos + 1);

            // Update the respective text objects
            GetText(mCurrentGameState, "artist-text-" + to_string(i + 1))->UpdateText(artistName);
            GetText(mCurrentGameState, "song-text-" + to_string(i + 1))->UpdateText(songName);
        }
        else
        {
            // Clear the text for invalid chart name formats
            GetText(mCurrentGameState, "artist-text-" + to_string(i + 1))->UpdateText("");
            GetText(mCurrentGameState, "song-text-" + to_string(i + 1))->UpdateText("");
        }
    }
}

void Game::GetCurrentChartDifficulties()
{
    // Get the currently selected chart directory
    if (mCurrentlyPreviewedCharts.empty() || mCurrentlyPreviewedCharts[3].empty())
    {
        // Clear mAllCurrentChartDifficulties and UI if no valid chart
        mAllCurrentChartDifficulties.clear();
        for (unsigned i = 0; i < 4; ++i)
        {
            GetText(mCurrentGameState, "difficulty-select-box-text-" + to_string(i + 1))->UpdateText("NO DIFFICULTIES");
        }
        return;
    }

    string chartDirectory = "charts/" + mCurrentlyPreviewedCharts[3];
    std::filesystem::path chartDirPath(chartDirectory);

    // Ensure the directory exists
    if (!std::filesystem::exists(chartDirPath) || !std::filesystem::is_directory(chartDirPath))
    {
        cerr << "Chart directory does not exist: " << chartDirectory << '\n';
        return;
    }

    // Iterate through .txt files in the directory
    mAllCurrentChartDifficulties.clear();

    for (const auto& entry : std::filesystem::directory_iterator(chartDirPath))
    {
        if (entry.is_regular_file() && entry.path().extension() == ".txt")
        {
            string difficultyName = entry.path().stem().string(); // File name without extension
            mAllCurrentChartDifficulties.push_back(difficultyName);
        }
    }
}

void Game::UpdateCurrentChartDifficulties()
{
    // Ensure there are difficulties to preview
    if (mAllCurrentChartDifficulties.empty())
    {
        mCurrentlyPreviewedDifficulties.fill("");
        for (unsigned i = 0; i < 4; ++i)
        {
            GetText(mCurrentGameState, "difficulty-select-box-text-" + to_string(i + 1))->UpdateText("NO DIFFICULTIES");
        }
        return;
    }

    // Update mCurrentlyPreviewedDifficulties based on circular queue logic
    unsigned totalDifficulties = mAllCurrentChartDifficulties.size();
    for (unsigned i = 0; i < 4; ++i)
    {
        unsigned currentIndex = (mChartDifficultyPreviewStartIndex + i) % totalDifficulties;
        mCurrentlyPreviewedDifficulties[i] = mAllCurrentChartDifficulties[currentIndex];
    }


    // Read difficulty values from the corresponding files and update UI
    regex difficultyRegex(R"(Difficulty\s*:\s*([\d.,]+))"); // Regex to match difficulty value
    for (unsigned i = 0; i < 4; ++i)
    {
        const string& difficultyName = mCurrentlyPreviewedDifficulties[i];
        if (difficultyName.empty())
        {
            GetText(mCurrentGameState, "difficulty-select-box-text-" + to_string(i + 1))->UpdateText("NO DIFFICULTIES");
            continue;
        }

        // Build the file path for the difficulty file
        string fileName = "charts/" + mCurrentlyPreviewedCharts[3] + "/" + difficultyName + ".txt";

        // Read the difficulty value from the file
        ifstream difficultyFile(fileName);
        if (!difficultyFile.is_open())
        {
            cerr << "Failed to open difficulty file: " << fileName << '\n';
            GetText(mCurrentGameState, "difficulty-select-box-text-" + to_string(i + 1))->UpdateText(difficultyName + " : ERROR");
            continue;
        }

        string line;
        string difficultyValue = "N/A"; // Default if no difficulty line found
        while (getline(difficultyFile, line))
        {
            smatch match;
            if (regex_search(line, match, difficultyRegex) && match.size() == 2)
            {
                difficultyValue = match[1].str();
                break; // Found the difficulty value, stop reading
            }
        }

        difficultyFile.close();

        // Update the text for the corresponding difficulty box
        string displayText = difficultyName + " : " + difficultyValue;
        GetText(mCurrentGameState, "difficulty-select-box-text-" + to_string(i + 1))->UpdateText(displayText);
    }

    mCurrentSongDifficulty = mCurrentlyPreviewedDifficulties[2];
}

void Game::HandleChartScrolling(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN && !mNewChartSpritesOnScreen)
    {
        unsigned totalCharts = mAllCharts.size();

        // Ensure there are charts to scroll through
        if (totalCharts == 0)
        {
            return;
        }

        switch (event.key.keysym.sym)
        {
        case SDLK_RIGHT:
            {
                // Increment start index and wrap around if necessary
                mChartPreviewStartIndex = (mChartPreviewStartIndex + 1) % totalCharts;

                // Update the currently previewed charts
                UpdateChartSelection();

                GetCurrentChartDifficulties();

                UpdateCurrentChartDifficulties();

                PlayCurrentlySelectedChartAudio();

                if (mCurrentGameState == GameState::CHART_SELECTION_MENU)
                    UpdateChartSelectionImage();
                else
                    GetChartMetadata();

                // Play the corresponding chart audio
                
                break;
            }
        case SDLK_LEFT:
            {
                // Decrement start index and wrap around if necessary
                if (mChartPreviewStartIndex == 0)
                {
                    mChartPreviewStartIndex = totalCharts - 1;
                }
                else
                {
                    mChartPreviewStartIndex = (mChartPreviewStartIndex - 1) % totalCharts;
                }

                // Update the currently previewed charts
                UpdateChartSelection();

                GetCurrentChartDifficulties();

                UpdateCurrentChartDifficulties();

                PlayCurrentlySelectedChartAudio();
                
                if (mCurrentGameState == GameState::CHART_SELECTION_MENU)
                    UpdateChartSelectionImage();
                else
                    GetChartMetadata();

                // Play the corresponding chart audio
                break;
            }
        case SDLK_RETURN:
            if (mCurrentGameState == GameState::CHART_SELECTION_MENU)
            {
                GetChartMetadata();
                TransitionToGameState(GameState::MAIN_GAMEPLAY);
                mSoundEngine->stopAllSounds();
            }
            else if (mCurrentGameState == GameState::CHART_EDITOR_SELECTION_MENU)
            {
                GetChartMetadata();
                TransitionToGameState(GameState::CHART_EDITOR);
                mSoundEngine->stopAllSounds();
            }
               
            break;
        default:
            // Do nothing for other keys
            return;
        }
    }
}

void Game::HandleDifficultyScrolling(SDL_Event& event)
{
    if (event.type != SDL_KEYDOWN)
        return;

    unsigned totalDifficulties = mAllCurrentChartDifficulties.size();
    if (totalDifficulties == 0)
        return;

    switch (event.key.keysym.sym)
    {
    case SDLK_UP:
        {
            // Decrement the start index (circularly)
            if (mChartDifficultyPreviewStartIndex == 0)
                mChartDifficultyPreviewStartIndex = totalDifficulties - 1;
            else
                --mChartDifficultyPreviewStartIndex;

            // Update the end index (circularly)
            mChartDifficultyPreviewEndIndex =
                (mChartDifficultyPreviewStartIndex + 3) % totalDifficulties;

            // Update the displayed difficulties
            GetCurrentChartDifficulties();
            UpdateCurrentChartDifficulties();
            GetChartMetadata();
            break;
        }

    case SDLK_DOWN:
        {
            // Increment the start index (circularly)
            mChartDifficultyPreviewStartIndex =
                (mChartDifficultyPreviewStartIndex + 1) % totalDifficulties;

            // Update the end index (circularly)
            mChartDifficultyPreviewEndIndex =
                (mChartDifficultyPreviewStartIndex + 3) % totalDifficulties;

            // Update the displayed difficulties;
            GetCurrentChartDifficulties();
            UpdateCurrentChartDifficulties();
            GetChartMetadata();
            break;
        }

    default:
        break;
    }
}

void Game::PlayCurrentlySelectedChartAudio()
{
    // Ensure there are charts and difficulties available
    if (mCurrentlyPreviewedCharts.empty() || mCurrentlyPreviewedDifficulties.empty())
    {
        cerr << "No charts or difficulties available to preview audio." << '\n';
        return;
    }

    // Get the chart folder name for the 4th index (0-based, index 3)
    string chartFolderName = mCurrentlyPreviewedCharts[3]; // 4th chart in preview

    // Get the selected difficulty file path
    string selectedDifficulty = mCurrentlyPreviewedDifficulties[2]; 
    string difficultyFilePath = "charts/" + chartFolderName + "/" + selectedDifficulty + ".txt";

    // Open the difficulty file
    ifstream difficultyFile(difficultyFilePath);
    if (!difficultyFile.is_open())
    {
        cerr << "Failed to open difficulty file: " << difficultyFilePath << '\n';
        return;
    }

    // Read the file line by line to find the "Audio : " line
    string line;
    string audioPath;
    regex audioRegex(R"(Audio\s*:\s*(.+))");

    while (getline(difficultyFile, line))
    {
        smatch match;
        if (regex_match(line, match, audioRegex))
        {
            if (match.size() == 2) // Ensure the match captures the path
            {
                audioPath = match[1].str();
                break;
            }
        }
    }

    mCurrentChartAudioFile = audioPath;

    difficultyFile.close();

    // Ensure an audio path was found
    if (audioPath.empty())
    {
        std::cerr << "No audio path found in difficulty file: " << difficultyFilePath << '\n';
        return;
    }

    // Stop currently playing audio (if any) and play the new audio
    if (mSoundEngine)
    {
        // Resolve the full path to the audio file
        std::filesystem::path fullAudioPath = std::filesystem::current_path() / audioPath;

        mSoundEngine->stopAllSounds();
        mSoundEngine->play2D(fullAudioPath.string().c_str(), true);// Play the new audio
        mCurrentSongDuration = mSoundEngine->getSoundSource(fullAudioPath.string().c_str())->getPlayLength();
    }
    else
    {
        cerr << "Sound engine is not initialized." << '\n';
    }
}

void Game::InitializeChartSelection()
{
    // Clear previous chart data
    mAllCharts.clear();

    GetCurrentChartDirectories();

    // Ensure mCurrentlyPreviewedCharts is updated

    mChartPreviewStartIndex = 0;
    
    UpdateChartSelection();

    GetCurrentChartDifficulties();

    UpdateCurrentChartDifficulties();

    PlayCurrentlySelectedChartAudio();

    if (mCurrentGameState == GameState::CHART_SELECTION_MENU)
        UpdateChartSelectionImage();

    mCurrentChartFile = "charts/" + mCurrentlyPreviewedCharts[3] + "/" + mCurrentlyPreviewedDifficulties[2] + ".txt";
}


void Game::GetChartMetadata()
{
    mCurrentChartFile = "charts/" + mCurrentlyPreviewedCharts[3] + "/" + mCurrentlyPreviewedDifficulties[2] + ".txt";
    mCurrentSongName = mCurrentlyPreviewedCharts[3];
    std::ifstream difficultyFile(mCurrentChartFile);

    std::string line;
    std::string imagePath;
    std::regex imageRegex(R"(Background Image\s*:\s*(.+))");
    std::regex bPMRegex(R"(BPM\s*:\s*(.+))");

    while (std::getline(difficultyFile, line))
    {
        std::smatch match;
        if (std::regex_match(line, match, imageRegex))
        {
            if (match.size() == 2) // Ensure the match captures the path
            {
                mCurrentChartImageFile = match[1].str();
            }
        }
        if (std::regex_match(line, match, bPMRegex))
        {
            if (match.size() == 2) // Ensure the match captures the path
            {
                mCurrentSongBPM = match[1].str();
            }
        }
    }
}

void Game::UpdateChartSelectionImage()
{
    GetChartMetadata();

    GetText(mCurrentGameState, "song-bpm-text")->UpdateText("BPM : "+mCurrentSongBPM);
    int minutes = static_cast<int>(mCurrentSongDuration / 60000); // Convert ms to minutes
    int seconds = (static_cast<int>(mCurrentSongDuration / 1000)) % 60; // Convert ms to seconds (mod 60)
    GetText(mCurrentGameState, "song-length-text")
        ->UpdateText("Length : " + to_string(minutes) + ":" + (seconds < 10 ? "0" : "") + to_string(seconds));

    // Convert file extension to lowercase for case-insensitive comparison
    std::string extension = fs::path(mCurrentChartImageFile).extension().string();
    std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

    // Check if the file is PNG or JPG and enable alpha accordingly
    bool useAlpha = extension == ".png";

    Texture bgImage = ResourceManager::loadTextureFromFile((fs::current_path().string() + "\\" + mCurrentChartImageFile).c_str(), useAlpha);
    GetSprite(mCurrentGameState, "song-cover")->SetTexture(bgImage);
}


void Game::CreateNewChart()
{
    // Step 1: Retrieve inputs from member variables
    string artistName = mNewChartArtistName;
    string songName = mNewChartSongName;
    string difficultyName = mNewChartDifficultyName;
    float difficulty = 0.00;
    string bpm = mNewChartBPM;
    string audioPath = mNewChartAudioPath;
    string imagePath = mNewChartImagePath;

    // Step 2: Create chart folder path
    string chartFolderName = artistName + "-" + songName;
    string chartFolderPath = "charts\\" + chartFolderName;

    try
    {
        // Step 3: Create directory
        if (!std::filesystem::exists("charts"))
        {
            std::filesystem::create_directory("charts");
        }
        std::filesystem::create_directory(chartFolderPath);

        // Step 4: Copy audio and image files into the folder
        std::string copiedAudioPath = chartFolderPath + "\\" + std::filesystem::path(audioPath).filename().string();
        std::string copiedImagePath = chartFolderPath + "\\" + std::filesystem::path(imagePath).filename().string();

        // Check if the audio file already exists in the directory
        if (!std::filesystem::exists(copiedAudioPath))
        {
            try
            {
                std::filesystem::copy_file(audioPath, copiedAudioPath, std::filesystem::copy_options::overwrite_existing);
            }
            catch (const std::filesystem::filesystem_error& e)
            {
                std::cerr << "Error copying audio file: " << e.what() << std::endl;
                // Handle the error if necessary (e.g., display a message or log it)
            }
        }
        else
        {
            std::cout << "Audio file already exists. Skipping copy: " << copiedAudioPath << std::endl;
        }

        // Check if the image file already exists in the directory
        if (!std::filesystem::exists(copiedImagePath))
        {
            try
            {
                std::filesystem::copy_file(imagePath, copiedImagePath, std::filesystem::copy_options::overwrite_existing);
            }
            catch (const std::filesystem::filesystem_error& e)
            {
                std::cerr << "Error copying image file: " << e.what() << std::endl;
                // Handle the error if necessary (e.g., display a message or log it)
            }
        }
        else
        {
            std::cout << "Image file already exists. Skipping copy: " << copiedImagePath << std::endl;
        }

        // Step 5: Create and write to the chart text file
        std::string chartFilePath = chartFolderPath + "\\" + difficultyName + ".txt";

        // Create and write to the chart filex
        std::ofstream chartFile(chartFilePath);

        if (chartFile.is_open())
        {
            chartFile << "Artist : " << artistName << "\n";
            chartFile << "Song Name : " << songName << "\n";
            chartFile << "Difficulty : " << difficulty << "\n";
            chartFile << "BPM : " << bpm << "\n";
            chartFile << "Background Image : " << copiedImagePath << "\n";
            chartFile << "Audio : " << copiedAudioPath << "\n";
            chartFile.close();
        }
        else
        {
            throw std::ios_base::failure("Failed to create chart text file.");
        }

        std::cout << "Chart successfully created at " << chartFolderPath << std::endl;
    }
    catch (const std::exception& e)
    {
        std::cerr << "Error creating chart: " << e.what() << std::endl;
    }
}

void Game::GetCurrentChartDirectories()
{
    // Iterate through the charts folder and store chart folder names
    const string chartDirectory = "charts";
    for (const auto& entry : std::filesystem::directory_iterator(chartDirectory))
    {
        if (entry.is_directory())
        {
            mAllCharts.push_back(entry.path().filename().string());
        }
    }
}