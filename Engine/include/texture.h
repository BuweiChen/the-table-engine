#pragma once

#include "SDL2/SDL.h"

class Texture : public Component {
    private:
        SDL_Texture* m_texture;
        SDL_Renderer* m_renderer;

        SDL_Rect* m_spriteBox;

    public:
        Texture();
        Texture(SDL_Texture* texture);

        SDL_Texture* getTexture();
        void setTexture(SDL_Texture* texture);

        void render() override;
};
