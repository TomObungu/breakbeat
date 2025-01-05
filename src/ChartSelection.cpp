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

                textTable.erase("new-chart-screen-artist-name-text");
                textTable.erase("new-chart-screen-artist-name-text-box");

                textTable.erase("new-chart-screen-difficulty-name-text");
                textTable.erase("new-chart-screen-difficulty-name-text-box");

                textTable.erase("new-chart-screen-song-bpm-text");
                textTable.erase("new-chart-screen-song-bpm-text-box");

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

void Game::UpdateChartSelection()
{
  unsigned totalCharts = mAllCharts.size();

    // Ensure valid state when no charts are available
    if (totalCharts == 0)
    {
        mCurrentlyPreviewedCharts.fill("");
        for (unsigned i = 0; i < 7; ++i)
        {
            GetText(mCurrentGameState, "artist-name-" + std::to_string(i + 1))->UpdateText("");
            GetText(mCurrentGameState, "song-text-" + std::to_string(i + 1))->UpdateText("");
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

    // Update the UI with artist and song names
    for (unsigned i = 0; i < 7; ++i)
    {
        const std::string& chartName = mCurrentlyPreviewedCharts[i];
        unsigned delimiterPos = chartName.find('-');
        if (delimiterPos != std::string::npos)
        {
            std::string artistName = chartName.substr(0, delimiterPos);
            std::string songName = chartName.substr(delimiterPos + 1);

            // Update the respective text objects
            GetText(mCurrentGameState, "artist-text-" + std::to_string(i + 1))->UpdateText(artistName);
            GetText(mCurrentGameState, "song-text-" + std::to_string(i + 1))->UpdateText(songName);
        }
        else
        {
            // Clear the text for invalid chart name formats
            GetText(mCurrentGameState, "artist-name-" + std::to_string(i + 1))->UpdateText("");
            GetText(mCurrentGameState, "song-text-" + std::to_string(i + 1))->UpdateText("");
        }
    }
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
                // Increment start index and wrap around if necessary
                mChartPreviewStartIndex = (mChartPreviewStartIndex + 1) % totalCharts;
                break;

            case SDLK_LEFT:
                // Decrement start index and wrap around if necessary
                if (mChartPreviewStartIndex == 0)
                {
                    mChartPreviewStartIndex = totalCharts - 1;
                }
                else
                {
                    mChartPreviewStartIndex = (mChartPreviewStartIndex - 1) % totalCharts;
                }
                break;

            default:
                // Do nothing for other keys
                return;
        }

        // Update the currently previewed charts
        UpdateChartSelection();
    }
}

void Game::InitializeChartSelection()
{
    // Clear previous chart data
    mAllCharts.clear();

    // Iterate through the charts folder and store chart folder names
    const std::string chartDirectory = "charts";
    for (const auto& entry : std::filesystem::directory_iterator(chartDirectory))
    {
        if (entry.is_directory())
        {
            mAllCharts.push_back(entry.path().filename().string());
        }
    }

    // Ensure mCurrentlyPreviewedCharts is updated
    UpdateChartSelection();
}

void Game::CreateNewChart()
{
    // Step 1: Retrieve inputs from member variables
    string artistName = mNewChartArtistName;
    string songName = mNewChartSongName;
    string difficultyName = mNewChartDifficultyName;
    string bpm = mNewChartBPM;
    string audioPath = mNewChartAudioPath;
    string imagePath = mNewChartImagePath;

    // Step 2: Create chart folder path
    string chartFolderName = artistName + "-" + songName;
    string chartFolderPath = "charts/" + chartFolderName;

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

        std::filesystem::copy_file(audioPath.substr(8), copiedAudioPath, std::filesystem::copy_options::overwrite_existing);
        std::filesystem::copy_file(imagePath.substr(8), copiedImagePath, std::filesystem::copy_options::overwrite_existing);

        // Step 5: Create and write to the chart text file
        std::string chartFilePath = chartFolderPath + "\\" + difficultyName + ".txt";

        // Create and write to the chart filex
        std::ofstream chartFile(chartFilePath);

        if (chartFile.is_open())
        {
            chartFile << "Artist : " << artistName << "\n";
            chartFile << "Song Name : " << songName << "\n";
            chartFile << "Difficulty Name : " << difficultyName << "\n";
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