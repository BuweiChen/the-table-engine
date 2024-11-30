#pragma once

#include "SDL2/SDL.h"

class Texture : public Component {
    private:
        SDL_Texture* m_texture;
        SDL_Renderer* m_renderer;

    public:
        Texture();

        SDL_Texture* getTexture();
        void setTexture(SDL_Texture* texture);

        void render() override;
};
