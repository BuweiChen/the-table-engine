#include <iostream>

#include "gameapp.h"
#include "SDL2/SDL.h"

int main()
{
    GameApplication app("Final project game app!");
    app.start();
    app.runLoop();

    SDL_Quit();
    return 0;
}