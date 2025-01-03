#include "Game.hpp"

void Game::HandleKeyboardInput(SDL_Event& event)
{
    if (mTypingMode)
    {
        if (event.type == SDL_KEYDOWN) // Wait for the next key press
        {
            SDL_Keycode keyCode = event.key.keysym.sym;

            // Handle Backspace key to delete the last character
            if (keyCode == SDLK_BACKSPACE)
            {
                std::string text = mCurrentTextBox->GetText();
                if (!text.empty()) // Check if there's text to delete
                {
                    text.pop_back(); // Remove the last character
                    mCurrentTextBox->UpdateText(text); // Update the text box
                }
            }
            // Handle spaces
            else if (keyCode == SDLK_SPACE)
            {
                std::string text = mCurrentTextBox->GetText();
                mCurrentTextBox->UpdateText(text + " ");
            }
            // Check if the key is a valid character (printable ASCII or explicitly letters)
            else if ((keyCode >= 32 && keyCode <= 126))
            {
                const char* keyName = SDL_GetKeyName(keyCode);
                if (keyName && strlen(keyName) == 1) // Ensure it's a single character
                {
                    char inputChar = keyName[0];

                    // Check Caps Lock and Shift states
                    SDL_Keymod keyMod = SDL_GetModState();
                    bool isShiftPressed = keyMod & KMOD_SHIFT;
                    bool isCapsLockOn = keyMod & KMOD_CAPS;

                    // Adjust case based on Shift and Caps Lock
                    if (inputChar >= 'A' && inputChar <= 'Z')
                    {
                        if (!(isCapsLockOn ^ isShiftPressed))
                        {
                            inputChar = inputChar + ('a' - 'A'); // Convert to lowercase
                        }
                    }
                    else if (inputChar >= 'a' && inputChar <= 'z')
                    {
                        if (isCapsLockOn ^ isShiftPressed)
                        {
                            inputChar = inputChar - ('a' - 'A'); // Convert to uppercase
                        }
                    }

                    std::string text = mCurrentTextBox->GetText();
                    mCurrentTextBox->UpdateText(text + inputChar);
                }
            }
            else if (keyCode == SDLK_RETURN) // Exit typing mode on Enter key
            {
                mTypingMode = false;
            }
        }
    }
}