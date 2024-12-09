#include <string>
#include <unordered_map>
#include <iostream>

#include "resourcemanager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

SDL_Renderer* ResourceManager::getRenderer()
{
    return m_renderer;
}

void ResourceManager::setRenderer(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}

// for images
SDL_Texture* ResourceManager::loadTexture(std::string path)
{
    if (m_imageResourceMap.find(path) != m_imageResourceMap.end())
    {
        return m_imageResourceMap[path];
    }

    if (SDL_LoadBMP(path.c_str()) == NULL)
    {
        std::cout << "Error loading image: " << path << std::endl;
        return NULL;
    } 

    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);
    
    m_imageResourceMap[path] = texture;
    return texture;
}

// for fonts
SDL_Texture* ResourceManager::loadText(std::string font_path, std::string text, SDL_Color color, int font_size)
{
    TTF_Font* font = NULL;
    std::string textKey = text + std::to_string(font_size);

    if (m_fontMap[textKey] != NULL)
    {
        font = m_fontMap[textKey];
    }
    else
    {
        font = TTF_OpenFont(font_path.c_str(), font_size);
        if (font == NULL)
        {
            std::cout << "Error loading font: " << font_path << std::endl;
            return NULL;
        }   
        m_fontMap[textKey] = font;
    }

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_FreeSurface(surface);
    
    return texture;
}

// for sounds
Sound* ResourceManager::loadSound(std::string path)
{
    Sound* sound = new Sound(path);
    return sound;
}
