#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

#include "gameapp.h"
#include "gameobject.h"
#include "resourcemanager.h"
#include "scenemanager.h"

#include "transform.h"
#include "texture.h"
#include "sound.h"

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
    if (TTF_Init() < 0) {
        std::cout << "TTF_Init Error: " << TTF_GetError() << std::endl;
    }

    ResourceManager::getInstance().setRenderer(m_renderer);

    SceneManager::getInstance().setRenderer(m_renderer);
    SceneManager::getInstance().getNextScene();

    Sound* music = ResourceManager::getInstance().loadSound("../Assets/Sounds/music.mp3");
    music->play(-1);
}

void GameApplication::printStats() {
    // render some stats on top left corner

    // number of enemies
    SDL_Color color = {255, 0, 0, 255};
    std::string numEnemies = std::to_string(SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Warrior").size());
    SDL_Texture* text = ResourceManager::getInstance().loadText("../Assets/Fonts/BruceForever.ttf", "Enemies: " + numEnemies, color, 12);
    SDL_Rect rect = {5, 0, 120, 25};
    SDL_RenderCopy(m_renderer, text, NULL, &rect);

    // FPS rounded to 2 decimal places
    color = {0, 0, 255, 255};
    std::stringstream fpsStream;
    fpsStream << std::fixed << std::setprecision(2) << m_FPS;
    std::string fps = fpsStream.str();

    text = ResourceManager::getInstance().loadText("../Assets/Fonts/BruceForever.ttf", "FPS: " + fps, color, 12);
    rect = {5, 15, 120, 25};
    SDL_RenderCopy(m_renderer, text, NULL, &rect);

    SDL_DestroyTexture(text);
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

        SceneManager::getInstance().input();
    }
}

void GameApplication::update() {
    SceneManager::getInstance().update();
}

void GameApplication::render() {
    SDL_SetRenderDrawColor(m_renderer, 100, 190, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(m_renderer);

    SceneManager::getInstance().render();
    printStats();

    SDL_RenderPresent(m_renderer);
}

void GameApplication::advanceFrame() {
    input();
    update();
    render();
}

void GameApplication::runLoop()
{
    int targetFPS = 60;
    int frameDelayInMs = 1000 / targetFPS;

    int frameNumber = 0;
    int lastFrameNumber = 0;
    int msCount = -1000;

    while(m_gameIsRunning) {
        Uint32 frameStartTime = SDL_GetTicks();

        advanceFrame();
        frameNumber++;

        int frameTimeDurationInMs = SDL_GetTicks() - frameStartTime;
        if (frameDelayInMs > frameTimeDurationInMs) {
            SDL_Delay(frameDelayInMs - frameTimeDurationInMs);
        }

        if (SDL_GetTicks() - msCount >= 1000) {
            m_FPS = frameNumber - lastFrameNumber;
            lastFrameNumber = frameNumber;
            msCount += 1000;
        } 
    }
}
