#include <iostream>
#include <string>

#include "gameapp.h"
#include "gameobject.h"
#include "resourcemanager.h"

#include "transform.h"
#include "renderer.h"

#include "SDL2/SDL.h"

GameObject* player;

// Constructor
GameApplication::GameApplication(std::string title) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return;
    } else {
        std::cout << "SDL_Init Success!" << std::endl;
    }

    const char* ctitle = title.c_str();
    m_window = SDL_CreateWindow(ctitle, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
        std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
        return;
    }
    
    m_renderer = SDL_CreateRenderer(m_window,-1,SDL_RENDERER_ACCELERATED);
}

// Destructor
GameApplication::~GameApplication() {
    // Destroy our renderer
    SDL_DestroyRenderer(m_renderer);
    // Destroy our window
    SDL_DestroyWindow(m_window);
}

void GameApplication::start() {
    // test player gameobject
    player = new GameObject("Player");

    auto renderer = new Renderer(m_renderer);
    ResourceManager::getInstance().setRenderer(m_renderer);
    SDL_Texture* texture = ResourceManager::getInstance().loadTexture("../Assets/test.bmp");
    renderer->setTexture(texture);

    auto transform = new Transform();
    transform->setSize(40, 40);
    transform->setPosition(200, 200);

    player->addComponent<Renderer>(renderer);
    player->addComponent<Transform>(transform);
}

// Handle input
void GameApplication::input() {
    SDL_Event event;
    // Start our event loop
    while (SDL_PollEvent(&event)) {
        // Handle each specific event
        if (event.type == SDL_QUIT) {
            m_gameIsRunning = false;
        }
    }
}

void GameApplication::update() {

}

void GameApplication::render() {
    SDL_SetRenderDrawColor(m_renderer, 100, 190, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);

    player->render();

    SDL_RenderPresent(m_renderer);
}

void GameApplication::advanceFrame() {
    input();
    update();
    render();
}

void GameApplication::runLoop()
{
    while(m_gameIsRunning) {
        advanceFrame();	
    }
}
