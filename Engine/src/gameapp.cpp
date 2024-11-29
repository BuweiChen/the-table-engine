#include <iostream>
#include <string>

#include "gameapp.h"
#include "gameobject.h"

#include "components/transform.cpp"

#include "SDL2/SDL.h"

// Constructor
GameApplication::GameApplication(std::string title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    } else {
        std::cout << "SDL_Init Success!" << std::endl;
    }

    const char* ctitle = title.c_str();
    mWindow = SDL_CreateWindow(ctitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (mWindow == NULL) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED);
}

// Destructor
GameApplication::~GameApplication() {
    // Destroy our renderer
    SDL_DestroyRenderer(mRenderer);
    // Destroy our window
    SDL_DestroyWindow(mWindow);
}

void GameApplication::Start() {
    // test player gameobject
    GameObject* player = new GameObject("Player");

    auto transform = new Transform();
    player->AddComponent<Transform>(transform);
}

// Handle input
void GameApplication::Input() {
    SDL_Event event;
    // Start our event loop
    while (SDL_PollEvent(&event)) {
        // Handle each specific event
        if (event.type == SDL_QUIT) {
            mGameIsRunning = false;
        }
    }
}

void GameApplication::Update() {
}

void GameApplication::Render() {
    SDL_SetRenderDrawColor(mRenderer, 100, 190, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(mRenderer);
    SDL_RenderPresent(mRenderer);
}

void GameApplication::AdvanceFrame() {
    Input();
    Update();
    Render();
}

void GameApplication::RunLoop()
{
    while(mGameIsRunning) {
        AdvanceFrame();	
    }
}
