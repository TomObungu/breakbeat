#include "Game.hpp"

void Game::HandleKeyboardInput(SDL_Event& event)
{
    if (mTypingMode)
    {
        if (event.type == SDL_KEYDOWN) // Wait for the next key press
        {
            SDL_Keycode keyCode = event.key.keysym.sym;

            // Define the maximum window size for the text box
            string text = mCurrentTextBox->GetText();

            // Handle Backspace key to delete the last character
            if (keyCode == SDLK_BACKSPACE)
            {
                if (!text.empty()) // Check if there's text to delete
                {
                    text.pop_back(); // Remove the last character
                    mCurrentTextBox->UpdateText(text);
                }
            }
            // Handle spaces
            else if (keyCode == SDLK_SPACE)
            {
                mCurrentTextBox->UpdateText(text += " ");
            }
            // Check if the key is a valid character (printable ASCII)
            else if ((keyCode >= 32 && keyCode <= 126))
            {
                const char* keyName = SDL_GetKeyName(keyCode);
                if (keyName && strlen(keyName) == 1) // Ensure it's a single character
                {
                    char inputChar = keyName[0];

                    // Check Shift state
                    SDL_Keymod keyMod = SDL_GetModState();
                    bool isShiftPressed = keyMod & KMOD_SHIFT;

                    // Map shifted keys for special characters
                    if (isShiftPressed)
                    {
                        switch (inputChar)
                        {
                            case '1': inputChar = '!'; break;
                            case '2': inputChar = '@'; break;
                            case '3': inputChar = '#'; break;
                            case '4': inputChar = '$'; break;
                            case '5': inputChar = '%'; break;
                            case '6': inputChar = '^'; break;
                            case '7': inputChar = '&'; break;
                            case '8': inputChar = '*'; break;
                            case '9': inputChar = '('; break;
                            case '0': inputChar = ')'; break;
                            case '-': inputChar = '_'; break;
                            case '=': inputChar = '+'; break;
                            case '[': inputChar = '{'; break;
                            case ']': inputChar = '}'; break;
                            case '\\': inputChar = '|'; break;
                            case ';': inputChar = ':'; break;
                            case '\'': inputChar = '"'; break;
                            case ',': inputChar = '<'; break;
                            case '.': inputChar = '>'; break;
                            case '/': inputChar = '?'; break;
                        }
                    }

                    // Check Caps Lock and adjust alphabetic case
                    bool isCapsLockOn = keyMod & KMOD_CAPS;
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

                    mCurrentTextBox->UpdateText(text += inputChar);
                }
            }
            else if (keyCode == SDLK_RETURN) // Exit typing mode on Enter key
            {
                mTypingMode = false;
            }
        }
    }
}
