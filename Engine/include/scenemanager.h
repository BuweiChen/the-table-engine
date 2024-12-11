#pragma once

/**
 * @file scenemanager.h
 * @brief Defines the SceneManager class for managing scenes in the game.
 *
 * The SceneManager class is responsible for handling scene transitions, 
 * rendering scenes, and managing the lifecycle of game objects within scenes.
 */

#include <string>
#include <atomic>

#include "scene.h"
#include <SDL2/SDL.h>
#include <nlohmann/json.hpp>

/**
 * @class SceneManager
 * @brief Singleton class that manages scenes and their transitions.
 *
 * This class implements the singleton pattern to manage scenes throughout the game. 
 * It provides mechanisms to switch scenes, render them, and manage game objects within them.
 */
class SceneManager
{
    private:
        SDL_Renderer* m_renderer; ///< Renderer used to render the game objects.
        std::vector<SceneTree*> m_sceneTrees; ///< Array of scene trees.

        int m_currentSceneIndex = 0; ///< Index of the current scene in the game.

        /**
         * @brief Private constructor for singleton pattern.
         */
        SceneManager() {}

        /**
         * @brief Deleted copy constructor to prevent copying of singleton.
         */
        SceneManager(const SceneManager&) = delete;

        /**
         * @brief Deleted assignment operator to prevent copying of singleton.
         */
        void operator=(const SceneManager&) = delete;

    public:
        /**
         * @brief Retrieves the singleton instance of SceneManager.
         * @return Reference to the singleton instance of SceneManager.
         */
        static SceneManager& getInstance();

        static std::atomic<uint64_t> m_totalObjects; ///< Total number of game objects created.
        static std::atomic<uint64_t> m_aliveObjects; ///< Current number of active game objects.

        /**
         * @brief Sets the renderer used for drawing game objects.
         * @param renderer Pointer to SDL_Renderer.
         */
        void setRenderer(SDL_Renderer* renderer);

        void loadScenesFromJSON(const std::string& filePath);

        /**
         * @brief Advances to the next scene based on the current scene index.
         */
        void getNextScene();

        /**
         * @brief Retrieves the current SDL_Renderer used by the SceneManager.
         * @return Pointer to SDL_Renderer.
         */
        SDL_Renderer* getRenderer();

        /**
         * @brief Retrieves the current scene tree managing the game objects.
         * @return Pointer to the current SceneTree.
         */
        SceneTree* getSceneTree();

        /**
         * @brief Cleans up the scene tree, removing all inactive game objects.
         */
        void cleanTree();

        /**
         * @brief Creates a test scene. This method is an example of how to define specific scenes.
         * @return Pointer to the created SceneTree.
         */
        SceneTree* createSceneTest1();
        SceneTree* createSceneTest2();
        SceneTree* createSceneTest3();

        /**
         * @brief Processes input for the current scene.
         */
        void input();

        /**
         * @brief Updates the state of the current scene.
         */
        void update();

        /**
         * @brief Renders the current scene.
         */
        void render();
};
