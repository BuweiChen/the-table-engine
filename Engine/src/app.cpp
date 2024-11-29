#include <iostream>

#include "gameapp.h"
#include "SDL2/SDL.h"

int main()
{
    GameApplication app("Final project game app!");
    app.Start();
    app.RunLoop();

    SDL_Quit();
    return 0;
}