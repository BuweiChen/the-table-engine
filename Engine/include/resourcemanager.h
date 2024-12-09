#pragma once

#include <string>
#include <unordered_map>

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

#include "sound.h"

class ResourceManager
{
    private:
        SDL_Renderer* m_renderer; // renderer to render the game objects
        std::unordered_map<std::string, SDL_Texture*> m_imageResourceMap; // cache texture resources
        std::unordered_map<std::string, TTF_Font*> m_fontMap; // cache font resources

        // private constructor
        ResourceManager() {}
        ResourceManager(const ResourceManager&) = delete;
        void operator=(const ResourceManager&) = delete;

    public:
        // singleton instance
        static ResourceManager& getInstance() {
            static ResourceManager instance;
            return instance;
        }

        void setRenderer(SDL_Renderer* renderer);
        SDL_Renderer* getRenderer();

        // for images
        SDL_Texture* loadTexture(std::string path);
        
        // for fonts
        SDL_Texture* loadText(std::string font_path, std::string text, SDL_Color color, int font_size = 20);

        // for sounds
        Sound* loadSound(std::string path);
};
