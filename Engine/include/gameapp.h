#pragma once

#include <string>

#include "SDL2/SDL.h"

struct GameApplication {
    SDL_Window* m_window = NULL;
    SDL_Renderer* m_renderer = NULL;
    bool m_gameIsRunning = true;

    float m_FPS = 0;

    // Constructor
    GameApplication(std::string title);
    ~GameApplication();

    void printStats();

    void start(); 
    void input();
    void update();
    void render();

    void advanceFrame();
    void runLoop();
};
