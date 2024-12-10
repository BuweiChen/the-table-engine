#pragma once

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// #include "sound.h"

/**
 * @file resourcemanager.h
 * @brief Manages resources such as textures, fonts, and potentially sounds for a game engine.
 *
 * The ResourceManager is designed as a singleton to ensure a single point of access
 * to all resource handling functionalities, including loading and managing textures and fonts.
 */

/**
 * @class ResourceManager
 * @brief Singleton class for managing game resources like textures and fonts.
 *
 * This class is responsible for loading, caching, and providing access to various
 * game resources, including textures and fonts, to reduce I/O overhead during gameplay.
 */
class ResourceManager
{
    private:
        SDL_Renderer* m_renderer; ///< Renderer used to render game objects.
        std::unordered_map<std::string, SDL_Texture*> m_imageResourceMap; ///< Cache of texture resources.
        std::unordered_map<std::string, TTF_Font*> m_fontMap; ///< Cache of font resources.

        /**
         * @brief Private constructor for singleton pattern.
         */
        ResourceManager() {}

        /**
         * @brief Deleted copy constructor to prevent multiple instances.
         */
        ResourceManager(const ResourceManager&) = delete;

        /**
         * @brief Deleted assignment operator to prevent multiple instances.
         */
        void operator=(const ResourceManager&) = delete;

    public:
        /**
         * @brief Retrieves the singleton instance of ResourceManager.
         * @return Reference to the singleton ResourceManager instance.
         */
        static ResourceManager& getInstance() {
            static ResourceManager instance;
            return instance;
        }

        /**
         * @brief Sets the renderer for resource management.
         * @param renderer Pointer to the SDL_Renderer to be used for rendering.
         */
        void setRenderer(SDL_Renderer* renderer);

        /**
         * @brief Gets the current renderer.
         * @return Pointer to the SDL_Renderer used for resource management.
         */
        SDL_Renderer* getRenderer();

        /**
         * @brief Loads a texture from a specified file path.
         * @param path Path to the image file.
         * @return Pointer to the loaded SDL_Texture.
         */
        SDL_Texture* loadTexture(std::string path);

        /**
         * @brief Loads a text as a texture using a specified TTF font.
         * @param font_path Path to the font file.
         * @param text Text string to render.
         * @param color SDL_Color for the text.
         * @param font_size Size of the font to be used (default is 20).
         * @return Pointer to the SDL_Texture containing the rendered text.
         */
        SDL_Texture* loadText(std::string font_path, std::string text, SDL_Color color, int font_size = 20);

        // Sound management methods can be added here in future.
        // Example:
        // /**
        //  * @brief Loads a sound file.
        //  * @param path Path to the sound file.
        //  * @return Pointer to the loaded Sound object.
        //  */
        // Sound* loadSound(std::string path);
};
