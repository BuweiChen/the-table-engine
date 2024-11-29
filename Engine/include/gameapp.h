#pragma once

#include <string>

#include "SDL2/SDL.h"

struct GameApplication {
    SDL_Window* mWindow = NULL;
    SDL_Renderer* mRenderer = NULL;
    bool mGameIsRunning = true;

    // Constructor
    GameApplication(std::string title);
    ~GameApplication();

    void Start(); 
    void Input();
    void Update();
    void Render();

    void AdvanceFrame();
    void RunLoop();
};
