#pragma once

#include "SDL2/SDL.h"

class Renderer : public Component {
    private:
        SDL_Renderer* m_renderer;
        SDL_Texture* m_texture;

    public:
        Renderer(SDL_Renderer* renderer);

        SDL_Renderer* getRenderer();
        SDL_Texture* getTexture();

        void setRenderer(SDL_Renderer* renderer);
        void setTexture(SDL_Texture* texture);

        void render() override;
};
