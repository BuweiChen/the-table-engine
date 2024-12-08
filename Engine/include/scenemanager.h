#pragma once

#include <string>

#include "scene.h"

#include <SDL2/SDL.h>

class SceneManager
{
    private:
        SDL_Renderer* m_renderer; // renderer to render the game objects
        SceneTree* m_sceneTree; // scene tree to manage game objects

        int m_currentSceneIndex = 0;

        // private constructor
        SceneManager() {}
        SceneManager(const SceneManager&) = delete;
        void operator=(const SceneManager&) = delete;

    public:
        // singleton instance
        static SceneManager& getInstance();

        static std::atomic<uint64_t> m_totalObjects;
        static std::atomic<uint64_t> m_aliveObjects;

        void setRenderer(SDL_Renderer* renderer);
        void getNextScene();
        SDL_Renderer* getRenderer();

        SceneTree* getSceneTree();

        // add all custom made scenes here
        SceneTree* createSceneTest1();

        void input();
        void update();
        void render();
};
