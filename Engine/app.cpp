#include <iostream>

#include "SDL2/SDL.h"

int main()
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    } else {
        std::cout << "SDL_Init Success!" << std::endl;
    }

    SDL_Window* window = nullptr;
    window = SDL_CreateWindow("An SDL2 Window", 0, 0, 640, 480, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return EXIT_FAILURE;
    }

    SDL_Event event;
    bool quit = false;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}