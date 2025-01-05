#include "Game.hpp"

void Game::LoadSettings()
{
    std::ifstream settingsFile(std::filesystem::current_path().string() + "\\settings.txt");
    if (!settingsFile.is_open()) {
        std::cerr << "Failed to open settings.txt" << std::endl;
        return;
    }

    std::string line;
    std::regex settingPattern(R"((\w+(?:\s\w+)*?)\s*:\s*(.*))");
    std::smatch match;

    while (std::getline(settingsFile, line)) {
        if (std::regex_match(line, match, settingPattern)) {
            const std::string& key = match[1];
            const std::string& value = match[2];

            if (key == "Scroll speed")
                mScrollSpeed = std::stoi(value);
            else if (key == "Receptor size")
                mReceptorSize = std::stoi(value);
            else if (key == "Scroll direction")
                mScrollDirection = value;
            else if (key == "Left keybind")
                mLeftKeybind = value;
            else if (key == "Down keybind")
                mDownKeybind = value;
            else if (key == "Up keybind")
                mUpKeybind = value;
            else if (key == "Right keybind")
                mRightKeybind = value;
        }
    }

    settingsFile.close();
}

void Game::UpdateSettings()
{
    std::ostringstream updatedSettings;

    updatedSettings << "Scroll speed : " << mScrollSpeed << '\n';
    updatedSettings << "Receptor size : " << mReceptorSize << '\n';
    updatedSettings << "Scroll direction : " << mScrollDirection << '\n';
    updatedSettings << "Left keybind : " << mLeftKeybind << '\n';
    updatedSettings << "Down keybind : " << mDownKeybind << '\n';
    updatedSettings << "Up keybind : " << mUpKeybind << '\n';
    updatedSettings << "Right keybind : " << mRightKeybind << '\n';

    std::ofstream settingsFile(std::filesystem::current_path().string() + "\\settings.txt");
    if (!settingsFile.is_open()) {
        std::cerr << "Failed to open settings.txt for writing" << std::endl;
        return;
    }

    settingsFile << updatedSettings.str();
    settingsFile.close();
}
