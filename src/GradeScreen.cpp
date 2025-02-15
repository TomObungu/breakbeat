#include "Game.hpp"

void Game::LoadScoreAndUpdateGradeScreen() 
{
    // Open the current score file
    ifstream scoreFile(mCurrentScoreFilePath);
    if (!scoreFile.is_open()) {
        cerr << "Error: Unable to open score file: " << mCurrentScoreFilePath << '\n';
        return;
    }

    // Read the score file data
    string line;
    regex keyValueRegex(R"(^(\w+)\s*:\s*(.+)$)"); // Matches "Key : Value" format
    regex currentGradeRegex(R"(Current Grade\s*:\s*(.+))");
    smatch match;

    // Variables to store parsed values
    string score, accuracy, flawless, perfect, great, good, bad, miss, currentGrade;

    while (getline(scoreFile, line)) {
        if (regex_match(line, match, keyValueRegex)) {
            string key = match[1];   // The key (e.g., "Score" or "Current Grade")
            string value = match[2]; // The value (e.g., "100000" or "A")

            // Map key to appropriate variable
            if (key == "Score") score = "Score : " + value;
            else if (key == "Accuracy") accuracy = "Accuracy : " + value;
            else if (key == "Flawless") flawless = "Flawless : " + value;
            else if (key == "Perfect") perfect = "Perfect : " + value;
            else if (key == "Great") great = "Great : " + value;
            else if (key == "Good") good = "Good : " + value;
            else if (key == "Bad") bad = "Bad : " + value;
            else if (key == "Miss") miss = "Miss : " + value;
        }
        if (std::regex_match(line, match, currentGradeRegex))
        {
            std::string key = match[1];   // The key (e.g., "Score" or "Current Grade")
            std::string value = match[2]; // The value (e.g., "100000" or "A")

            if (match.size() == 2) // Ensure the match captures the path
            {
                currentGrade = match[1].str();
            }
        }
    }
    scoreFile.close();


    // Update texts on the grade screen
    GetText(GameState::GRADE_SCREEN, "gameplay-score")->UpdateText(score);
    GetText(GameState::GRADE_SCREEN, "gameplay-accuracy")->UpdateText(accuracy);
    GetText(GameState::GRADE_SCREEN, "gameplay-flawless-count")->UpdateText(flawless);
    GetText(GameState::GRADE_SCREEN, "gameplay-perfect-count")->UpdateText(perfect);
    GetText(GameState::GRADE_SCREEN, "gameplay-great-count")->UpdateText(great);
    GetText(GameState::GRADE_SCREEN, "gameplay-good-count")->UpdateText(good);
    GetText(GameState::GRADE_SCREEN, "gameplay-bad-count")->UpdateText(bad);
    GetText(GameState::GRADE_SCREEN, "gameplay-miss-count")->UpdateText(miss);

    // Assuming "grade" holds the value of the Current Grade, retrieved earlier
    if (!currentGrade.empty()) {
        std::string textureName;

        // Map the grade to the corresponding texture name
        if (currentGrade == "A") {
            textureName = "main-gameplay-grade-screen-A";
        }
        else if (currentGrade == "B") {
            textureName = "main-gameplay-grade-screen-B";
        }
        else if (currentGrade == "C") {
            textureName = "main-gameplay-grade-screen-C";
        }
        else if (currentGrade == "D") {
            textureName = "main-gameplay-grade-screen-D";
        }
        else if (currentGrade == "F") {
            textureName = "main-gameplay-grade-screen-F";
        }
        else if (currentGrade == "S") {
            textureName = "main-gameplay-grade-screen-S";
        }
        else {
            std::cerr << "Warning: Unknown grade value: " << currentGrade << '\n';
            textureName = ""; // No texture for unknown grade
        }

        // Set the sprite texture if a valid texture name is determined
        if (!textureName.empty()) {
            auto gradeSprite = GetSprite(GameState::GRADE_SCREEN, "main-gameplay-grade-screen-grade");
            if (gradeSprite) {
                gradeSprite->SetTexture(ResourceManager::GetTexture(textureName));
            }
            else {
                std::cerr << "Error: Failed to retrieve sprite for 'main-gameplay-grade-screen-grade'" << std::endl;
            }
        }
    }

    std::cout << "Grade screen updated with score data from: " << mCurrentScoreFilePath << '\n';
}
