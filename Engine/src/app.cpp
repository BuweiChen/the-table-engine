#include <iostream>

#include "gameapp.h"
#include "SDL2/SDL.h"

int main(int argc, char* argv[])
{
    GameApplication app("Final project game app!");

    if (argc > 1 && std::string(argv[1]) == "demo") {
        std::cout << "Loading demo scene..." << std::endl;
        app.start(true);
    } else {
        std::cout << "Loading scenes from JSON..." << std::endl;
        app.start(false);
    }
    
    app.runLoop();

    SDL_Quit();
    return 0;
}