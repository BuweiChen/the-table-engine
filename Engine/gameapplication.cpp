#include <iostream>
#include <string>

#include "SDL2/SDL.h"

struct GameApplication {
    SDL_Window* mWindow = NULL;
    SDL_Renderer* mRenderer = NULL;
    bool mGameIsRunning = true;

    // Constructor
    GameApplication(std::string title) {
        const char* ctitle = title.c_str();
        mWindow = SDL_CreateWindow(ctitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
        if (mWindow == NULL) {
            std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
            return;
        }
        mRenderer = SDL_CreateRenderer(mWindow,-1,SDL_RENDERER_ACCELERATED);
    }

    // Destructor
    ~GameApplication() {
        // Destroy our renderer
        SDL_DestroyRenderer(mRenderer);
        // Destroy our window
        SDL_DestroyWindow(mWindow);
    }

    // Handle input
    void Input() {
        SDL_Event event;
        // Start our event loop
        while (SDL_PollEvent(&event)) {
                // Handle each specific event
                if (event.type == SDL_QUIT) {
                        mGameIsRunning = false;
                }
        }
    }

    void Update() {
    }

    void Render() {
        SDL_SetRenderDrawColor(mRenderer, 100, 190, 255, SDL_ALPHA_OPAQUE);
        SDL_RenderClear(mRenderer);
        SDL_RenderPresent(mRenderer);
    }

    void AdvanceFrame() {
        Input();
        Update();
        Render();
    }

    void RunLoop()
    {
        while(mGameIsRunning) {
            AdvanceFrame();	
        }
    }
};
