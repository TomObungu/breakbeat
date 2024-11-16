/*

The breakbeat.cpp file that is responsible for containing the
int main() function required to produce a working executable file
from the compiler

*/

#include "Game.hpp"

int main(int argc, char* argv[])
{
    // Instantiate game object
    Game game;
    game.Run();  // Start the main game loop
    return EXIT_SUCCESS;
}
