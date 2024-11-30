#pragma once

#include <string>

#include "scene.h"

#include <SDL2/SDL.h>

class SceneManager
{
    private:
        SDL_Renderer* m_renderer; // renderer to render the game objects
        SceneTree* m_sceneTree; // scene tree to manage game objects

        // private constructor
        SceneManager() {}
        SceneManager(const SceneManager&) = delete;
        void operator=(const SceneManager&) = delete;

    public:
        // singleton instance
        static SceneManager& getInstance();

        void setRenderer(SDL_Renderer* renderer);
        void setSceneTree(SceneTree* sceneTree);

        SceneTree* createScene1();

        void input();
        void update();
        void render();
};
