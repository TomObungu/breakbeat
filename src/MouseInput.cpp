#include "Game.hpp"

void Game::HandleMouseInput(SDL_Event& event)
{
    if (event.type == SDL_MOUSEMOTION)
    {
        // Update mouse position based on the event
        // Check for colliding sprite in the current game state
        Sprite* collidingSprite = CheckCollidingSprite(mCurrentGameState);

        if (collidingSprite)
        {
            // Handle collisions based on the current game state
            Menu* currentMenu = nullptr;

            if (mCurrentGameState == GameState::START_MENU)
            {
                currentMenu = GetMenu(GameState::START_MENU, "start-menu");

                if (collidingSprite == GetSprite(GameState::START_MENU, "start-button"))
                {
                    currentMenu->PlayUnhighlightAnimation();
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlayHighlightAnimation();
                }
                else if (collidingSprite == GetSprite(GameState::START_MENU, "exit-button"))
                {
                    currentMenu->PlayUnhighlightAnimation();
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlayHighlightAnimation();
                }
            }
            else if (mCurrentGameState == GameState::MAIN_MENU)
            {
                currentMenu = GetMenu(GameState::MAIN_MENU, "main-menu");

                if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-back-button"))
                {
                    if(currentMenu->GetCurrentMenuOption() != GetSprite(GameState::MAIN_MENU, "main-menu-back-button"))
                    {
                        currentMenu->PlayUnhighlightAnimation();
                        currentMenu->SetCurrentMenuOption(collidingSprite);
                        currentMenu->PlayHighlightAnimation();
                    }
                }
                else if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-chart-editor-button"))
                {
                    if(currentMenu->GetCurrentMenuOption() != GetSprite(GameState::MAIN_MENU, "main-menu-chart-editor-button"))
                    {
                        currentMenu->PlayUnhighlightAnimation();
                        currentMenu->SetCurrentMenuOption(collidingSprite);
                        currentMenu->PlayHighlightAnimation();
                    }
                }
                else if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-chart-selection-button"))
                {
                    if(currentMenu->GetCurrentMenuOption() != GetSprite(GameState::MAIN_MENU, "main-menu-chart-selection-button"))
                    {
                        currentMenu->PlayUnhighlightAnimation();
                        currentMenu->SetCurrentMenuOption(collidingSprite);
                        currentMenu->PlayHighlightAnimation();
                    }
                }
                else if (collidingSprite == GetSprite(GameState::MAIN_MENU, "main-menu-settings-button"))
                {
                    if(currentMenu->GetCurrentMenuOption() != GetSprite(GameState::MAIN_MENU, "main-menu-settings-button"))
                    {
                        currentMenu->PlayUnhighlightAnimation();
                        currentMenu->SetCurrentMenuOption(collidingSprite);
                        currentMenu->PlayHighlightAnimation();
                    }
                }
            }
        }
    }
    else if (event.type == SDL_MOUSEBUTTONDOWN)
    {
        Sprite* collidingSprite = CheckCollidingSprite(mCurrentGameState);
        Text* collidingText = CheckCollidingText(mCurrentGameState);

        if (collidingSprite)
        {
            Menu* currentMenu = nullptr;

            if (mCurrentGameState == GameState::START_MENU)
            {
                currentMenu = GetMenu(GameState::START_MENU, "start-menu");

                if (collidingSprite == GetSprite(GameState::START_MENU, "start-button"))
                {
                    TransitionToGameState(GameState::MAIN_MENU);
                }
                else if (collidingSprite == GetSprite(GameState::START_MENU, "exit-button"))
                {
                    mWindow.SetWindowClosedBoolean(true);
                }
            }
            else if( mCurrentGameState == GameState::MAIN_MENU)
            {

                currentMenu = GetMenu(GameState::MAIN_MENU, "main-menu");

                if (collidingSprite == GetSprite(mCurrentGameState, "main-menu-settings-button"))
                {
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlaySelectionAnimation();
                    if(currentMenu->GetCurrentMenuOption()->IsAnimationComplete())
                        TransitionToGameState(GameState::SETTINGS);
                }
                else if (collidingSprite == GetSprite(mCurrentGameState, "main-menu-back-button"))
                {
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlaySelectionAnimation();
                    TransitionToGameState(GameState::START_MENU);
                }
                else if (collidingSprite == GetSprite(mCurrentGameState, "main-menu-chart-editor-button"))
                {
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlaySelectionAnimation();
                    TransitionToGameState(GameState::CHART_EDITOR_SELECTION_MENU);
                }                
                else if (collidingSprite == GetSprite(mCurrentGameState, "main-menu-chart-selection-button"))
                {
                    currentMenu->SetCurrentMenuOption(collidingSprite);
                    currentMenu->PlaySelectionAnimation();
                    TransitionToGameState(GameState::CHART_SELECTION_MENU);
                }
            }
            else if( mCurrentGameState == GameState::SETTINGS)
            {
                Menu* settingsMenu = GetMenu(mCurrentGameState, "settings-menu");
                
                if (mSelectedSetting)
                {
                    Text* currentText = settingsMenu->GetCurrentTextOption();

                    if (currentText == GetText(mCurrentGameState, "scroll-speed-text"))
                    {
                        if (collidingSprite == GetSprite(mCurrentGameState, "settings-increment-right-1"))
                        {
                            mScrollSpeed++;
                            currentText->UpdateText(std::to_string(mScrollSpeed));
                            UpdateSettings();
                        }
                        else if (collidingSprite == GetSprite(mCurrentGameState, "settings-increment-left-1"))
                        {
                            mScrollSpeed--;
                            currentText->UpdateText(std::to_string(mScrollSpeed));
                            UpdateSettings();
                        }
                    }
                    else if (currentText == GetText(mCurrentGameState, "receptor-size-text"))
                    {
                        if (collidingSprite == GetSprite(mCurrentGameState, "settings-increment-right-2"))
                        {
                            mReceptorSize++;
                            currentText->UpdateText(std::to_string(mReceptorSize) + "%");
                            UpdateSettings();
                        }
                        else if (collidingSprite == GetSprite(mCurrentGameState,"settings-increment-left-2"))
                        {
                            mReceptorSize--;
                            currentText->UpdateText(std::to_string(mReceptorSize) + "%");
                            UpdateSettings();
                        }
                    }
                    else if(currentText == GetText(mCurrentGameState, "scroll-direction-text"))
                    {
                        if (collidingSprite == GetSprite(mCurrentGameState, "settings-increment-right-3") || 
                        collidingSprite == GetSprite(mCurrentGameState,"settings-increment-left-3"))
                        {
                            if (currentText->GetText() == "Down")
                            {
                                currentText->UpdateText("Up");
                                mScrollDirection = "Up";
                                UpdateSettings();
                            }
                            else if (currentText->GetText() == "Up")
                            {
                                currentText->UpdateText("Down");
                                mScrollDirection = "Down";
                                UpdateSettings();
                            }
                        }
                    }
                }
            }
            else if (mCurrentGameState == GameState::CHART_EDITOR_SELECTION_MENU)
            {
                if (collidingSprite == GetSprite(mCurrentGameState, "chart-editor-new-chart-button") && !mShowNewChartScreen)
                {
                    // Open file explorer and store the selected path in mNewChartAudioPath
                    const char* filterPatterns[] = {"*.mp3", "*.wav", "*.ogg"};
                    const char* path = tinyfd_openFileDialog(
                        "Select Audio File",  // Title of the dialog
                        "",                   // Default path (empty for current directory)
                        3,                    // Number of filter patterns
                        filterPatterns,       // File type filters
                        "Audio Files (*.mp3, *.wav, *.ogg)", // Description of filters
                        0                     // Single selection (0: single file, 1: multiple files)
                    );

                    if (path) // If a file was selected
                        mNewChartAudioPath = string(path);
                    else mNewChartAudioPath = ""; // Return an empty string if the user cancels

                    if (!mNewChartAudioPath.empty())
                    {
                        mShowNewChartScreen = true; // Show the new chart screen if a valid path is selected
                    }
                    else
                    {
                        mShowNewChartScreen = false; // Do not show the screen if no file is selected
                    }
                }
                else if (collidingSprite == GetSprite(mCurrentGameState, "chart-editor-menu-difficulty-new-difficulty-button") && !mShowNewDifficultyScreen)
                {
                    mShowNewDifficultyScreen = true;
                }
                else if (mNewChartSpritesOnScreen)
                {
                    if (collidingSprite != GetSprite(mCurrentGameState, "z-chart-editor-new-chart-user-interface") &&
                        collidingSprite != GetSprite(mCurrentGameState, "zz-chart-editor-new-chart-create-button") &&
                        collidingSprite != GetSprite(mCurrentGameState, "zz-chart-editor-new-chart-user-interface-box-new-image"))
                    {
                        mShowNewChartScreen = false;
                        removingSprites = true; 
                    }
                    else if(collidingSprite == GetSprite(mCurrentGameState, "zz-chart-editor-new-chart-user-interface-box-new-image"))
                    {
                        // Open file dialog to select the image
                        const char* filterPatterns[] = {"*.png", "*.jpg", "*.jpeg", "*.bmp"};
                        const char* imagePath = tinyfd_openFileDialog(
                            "Select Image File",                 // Title of the dialog
                            "",                                  // Default path
                            4,                                   // Number of filter patterns
                            filterPatterns,                      // Image file extensions
                            "Image Files (*.png, *.jpg, *.jpeg, *.bmp)", // Description of filters
                            0                                    // Single selection mode
                        );
                        if (imagePath) // If a file was selected
                        {
                            mNewChartImagePath = std::string(imagePath);
                            GetText(mCurrentGameState,"new-chart-screen-chart-image-text")->UpdateText("Image : "+mNewChartImagePath);
                        }
                        else
                        {
                            mNewChartImagePath = ""; // If no file was selected, leave it empty
                        }
                    }
                    else if(collidingText == GetText(mCurrentGameState, "new-chart-screen-song-name-text"))
                    {
                        if(!mTypingMode)
                        {
                            mCurrentTextBox = GetText(mCurrentGameState,"new-chart-screen-song-name-text-box");
                            mTypingMode = true;
                        }
                    }
                    else if(collidingText == GetText(mCurrentGameState, "new-chart-screen-artist-name-text"))
                    {
                        if(!mTypingMode)
                        {
                            mCurrentTextBox = GetText(mCurrentGameState,"new-chart-screen-artist-name-text-box");
                            mTypingMode = true;
                        }
                    }
                    else if(collidingText == GetText(mCurrentGameState, "new-chart-screen-difficulty-name-text"))
                    {
                        if(!mTypingMode)
                        {
                            mCurrentTextBox = GetText(mCurrentGameState,"new-chart-screen-difficulty-name-text-box");
                            mTypingMode = true;
                        }
                    }
                    else if(collidingText == GetText(mCurrentGameState, "new-chart-screen-song-bpm-text"))
                    {
                        if(!mTypingMode)
                        {
                            mCurrentTextBox = GetText(mCurrentGameState,"new-chart-screen-song-bpm-text-box");
                            mTypingMode = true;
                        }
                    }
                    else if(collidingSprite == GetSprite(mCurrentGameState, "zz-chart-editor-new-chart-create-button"))
                    {
                        mNewChartSongName = GetText(mCurrentGameState, "new-chart-screen-song-name-text-box")->GetText();
                        mNewChartArtistName = GetText(mCurrentGameState, "new-chart-screen-artist-name-text-box")->GetText();
                        mNewChartDifficultyName = GetText(mCurrentGameState, "new-chart-screen-difficulty-name-text-box")->GetText();
                        mNewChartBPM = GetText(mCurrentGameState, "new-chart-screen-song-bpm-text-box")->GetText();
                        mNewChartImagePath = GetText(mCurrentGameState, "new-chart-screen-chart-image-text")->GetText().substr(8);
                        mNewChartAudioPath = GetText(mCurrentGameState, "new-chart-screen-chart-audio-text")->GetText().substr(8);

                        CreateNewChart();
                    }
                }
                else if (mNewDifficultySpritesOnScreen)
                {
                    if (collidingSprite != GetSprite(mCurrentGameState, "z-chart-editor-new-difficullty-user-interface-box") &&
                        collidingSprite != GetSprite(mCurrentGameState, "zz-chart-editor-new-difficulty-create-button") &&
                        collidingSprite != GetSprite(mCurrentGameState, "zz-chart-editor-new-difficulty-user-interface-box-new-image"))
                    {
                        mShowNewDifficultyScreen = false;
                        removingSprites = true;
                    }
                    if (collidingText == GetText(mCurrentGameState, "new-difficulty-screen-difficulty-name-text"))
                    {
                        if (!mTypingMode)
                        {
                            mCurrentTextBox = GetText(mCurrentGameState, "new-difficulty-screen-difficulty-name-text-box");
                            mTypingMode = true;
                        }
                    }
                    else if (collidingSprite == GetSprite(mCurrentGameState, "zz-chart-editor-new-difficulty-user-interface-box-new-image"))
                    {
                        // Open file dialog to select the image
                        const char* filterPatterns[] = { "*.png", "*.jpg", "*.jpeg", "*.bmp" };
                        const char* imagePath = tinyfd_openFileDialog(
                            "Select Image File",                 // Title of the dialog
                            "",                                  // Default path
                            4,                                   // Number of filter patterns
                            filterPatterns,                      // Image file extensions
                            "Image Files (*.png, *.jpg, *.jpeg, *.bmp)", // Description of filters
                            0                                    // Single selection mode
                        );
                        if (imagePath) // If a file was selected
                        {
                            mNewChartImagePath = std::string(imagePath);
                            GetText(mCurrentGameState, "new-difficulty-screen-chart-image-text")->UpdateText("Image : " + mNewChartImagePath);
                        }
                        else
                        {
                            mNewChartImagePath = ""; // If no file was selected, leave it empty
                        }
                    }
                    else if (collidingSprite == GetSprite(mCurrentGameState, "zz-chart-editor-new-difficulty-create-button"))
                    {
                        // Get the directory of the currently selected chart
                        std::string chartDirectory = "charts\\" + mCurrentlyPreviewedCharts[3];
                        std::filesystem::path chartDirPath(chartDirectory);

                        // Ensure the directory exists
                        if (!std::filesystem::exists(chartDirPath) || !std::filesystem::is_directory(chartDirPath))
                        {
                            cerr << "Chart directory does not exist: " + chartDirectory + '\n';
                            return;
                        }

                        // Path to the chart difficulty file (assuming a consistent file naming convention)
                        std::string fileName = chartDirectory + "\\" + mCurrentlyPreviewedDifficulties[2] + ".txt";

                        // Open and read the chart difficulty file
                        std::ifstream difficultyFile(fileName);
                        if (!difficultyFile.is_open())
                        {
                            cerr << "Failed to open difficulty file: " + fileName + '\n';
                            return;
                        }

                        // Regex patterns for extracting chart details
                        std::regex songNameRegex(R"(Song Name\s*:\s*(.+))");
                        std::regex artistNameRegex(R"(Artist\s*:\s*(.+))");
                        std::regex bpmRegex(R"(BPM\s*:\s*(.+))");
                        std::regex audioPathRegex(R"(Audio\s*:\s*(.+))");
                        std::regex imagePathRegex(R"(Background Image\s*:\s*(.+))");

                        // Variables to store extracted data
                        std::string songName, artistName, bpm, audioPath, imagePath;

                        std::string line;
                        while (std::getline(difficultyFile, line))
                        {
                            std::smatch match;

                            if (std::regex_search(line, match, songNameRegex) && match.size() == 2)
                            {
                                songName = match[1].str();
                            }
                            else if (std::regex_search(line, match, artistNameRegex) && match.size() == 2)
                            {
                                artistName = match[1].str();
                            }
                            else if (std::regex_search(line, match, bpmRegex) && match.size() == 2)
                            {
                                bpm = match[1].str();
                            }
                            else if (std::regex_search(line, match, audioPathRegex) && match.size() == 2)
                            {
                                audioPath = match[1].str();
                            }
                            else if (std::regex_search(line, match, imagePathRegex) && match.size() == 2)
                            {
                                imagePath = match[1].str();
                            }
                        }
                        difficultyFile.close();
                        
                        // Get user input for new difficulty and image
                        std::string newDifficultyName = GetText(mCurrentGameState, "new-difficulty-screen-difficulty-name-text-box")->GetText();
                        std::string newImagePath = GetText(mCurrentGameState, "new-difficulty-screen-chart-image-text")->GetText().substr(8);

                        if (newDifficultyName.empty())
                        {
                        std::cerr << "New difficulty name cannot be empty" << '\n';
                            return;
                        }

                        // Set default values for the new chart
                        mNewChartSongName = songName;
                        mNewChartArtistName = artistName;
                        mNewChartBPM = bpm;
                        mNewChartAudioPath = audioPath;
                        mNewChartImagePath = newImagePath.empty() ? imagePath : newImagePath;
                        mNewChartDifficultyName = newDifficultyName;

                        CreateNewChart();
                    }
                }
            }
        }
    }
}

Sprite* Game::CheckCollidingSprite(GameState gameState)
{
    // Define relevant sprites for each game state
    std::vector<std::string> relevantSprites;

    if (gameState == GameState::START_MENU)
    {
        relevantSprites = {"start-button", "exit-button"};
    }
    else if (gameState == GameState::MAIN_MENU)
    {
        relevantSprites = {"main-menu-back-button", "main-menu-chart-editor-button", "main-menu-chart-selection-button", "main-menu-settings-button"};
    }
    else if (gameState == GameState::SETTINGS)
    {
        relevantSprites = {"settings-increment-left-1", "settings-increment-left-2", "settings-increment-left-3", "settings-increment-right-1", "settings-increment-right-2","settings-increment-right-3"};
    }
    else if (gameState == GameState::CHART_EDITOR_SELECTION_MENU)
    {
        // Reorder relevantSprites to prioritize specific sprites
        if(mShowNewChartScreen)
            relevantSprites = {
                "zz-chart-editor-new-chart-user-interface-box-new-image",
                "zz-chart-editor-new-chart-create-button",
                "z-chart-editor-new-chart-user-interface",
                "chart-editor-new-chart-button",
                "chart-editor-selection-menu-ua"
            };
        else if(mShowNewDifficultyScreen)
            relevantSprites = {
                "zz-chart-editor-new-difficulty-user-interface-box-new-image",
                "zz-chart-editor-new-difficulty-create-button",
                "z-chart-editor-new-difficullty-user-interface-box",
                "chart-editor-new-chart-button",
                "chart-editor-selection-menu-ua"
            };
        else
            relevantSprites = {
                "chart-editor-new-chart-button",
                "chart-editor-menu-difficulty-new-difficulty-button"
            };


    }

    // Collect colliding sprites
    std::vector<std::string> collidingSprites;

    for (auto& [key, sprite] : mSpriteRenderer.mCurrentlyRenderedSprites[gameState])
    {
        if (std::find(relevantSprites.begin(), relevantSprites.end(), key) != relevantSprites.end())
        {
            bool CollisionX = (mMouse->GetMouseCoordinate().x + mMouse->GetMouseSize().x >= sprite->GetPosition().x) &&
                            (sprite->GetPosition().x + sprite->GetSize().x >= mMouse->GetMouseCoordinate().x);

            bool CollisionY = (mMouse->GetMouseCoordinate().y + mMouse->GetMouseSize().y >= sprite->GetPosition().y) &&
                            (sprite->GetPosition().y + sprite->GetSize().y >= mMouse->GetMouseCoordinate().y);


            if (CollisionX && CollisionY)
            {
                collidingSprites.push_back(key);
            }
        }
    }

    // Determine which sprite to return based on priority
    for (const auto& relevantKey : relevantSprites)
    {
        auto it = std::find(collidingSprites.begin(), collidingSprites.end(), relevantKey);
        if (it != collidingSprites.end())
        {
            return GetSprite(mCurrentGameState,relevantKey);
        }
    }

    return nullptr; // No collision detected
}

Text* Game::CheckCollidingText(GameState gameState)
{
    // Define relevant texts for CHART_EDITOR_SELECTION_MENU
    std::vector<std::string> relevantTexts;

    if (gameState == GameState::CHART_EDITOR_SELECTION_MENU)
    {
        relevantTexts = 
        {
            "new-chart-screen-song-name-text",
            "new-chart-screen-artist-name-text",
            "new-chart-screen-song-bpm-text",
            "new-chart-screen-difficulty-name-text",
            "new-difficulty-screen-difficulty-name-text"
        };
    }

    // Collect colliding texts
    std::vector<std::string> collidingTexts;

    for (auto& [key, text] : mTextRenderer.mCurrentlyRenderedTexts[gameState])
    {
        if (std::find(relevantTexts.begin(), relevantTexts.end(), key) != relevantTexts.end())
        {
            bool CollisionX = (mMouse->GetMouseCoordinate().x + mMouse->GetMouseSize().x >= text->mPosition.x) &&
                              (text->mPosition.x + text->GetSize().x >= mMouse->GetMouseCoordinate().x);

            bool CollisionY = (mMouse->GetMouseCoordinate().y + mMouse->GetMouseSize().y >= text->mPosition.y) &&
                              (text->mPosition.y + text->GetSize().y >= mMouse->GetMouseCoordinate().y);

            if (CollisionX && CollisionY)
            {
                collidingTexts.push_back(key);
            }
        }
    }

    // Determine which text to return based on priority
    for (const auto& relevantKey : relevantTexts)
    {
        auto it = std::find(collidingTexts.begin(), collidingTexts.end(), relevantKey);
        if (it != collidingTexts.end())
        {
            std::cout << relevantKey << '\n';
            return GetText(mCurrentGameState, relevantKey);
        }
    }

    return nullptr; // No collision detected
}