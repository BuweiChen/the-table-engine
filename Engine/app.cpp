#include <iostream>

#include "gameapplication.cpp"

#include "SDL2/SDL.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "SDL_Init Success!" << std::endl;
    }

    GameApplication app("Final project game app!");
    app.RunLoop();

    SDL_Quit();
    return 0;
}