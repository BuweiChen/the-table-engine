#pragma once

#include "SDL2/SDL.h"

class Texture : public Component {
    private:
        SDL_Texture* m_texture;
        SDL_Renderer* m_renderer;

        SDL_Rect* m_spriteBox;
        SDL_Rect* m_spriteClip; // section of sprite box rendered
        int m_rows, m_cols;
        float m_time;

    public:
        Texture();
        Texture(SDL_Texture* texture);

        SDL_Texture* getTexture();
        void setTexture(SDL_Texture* texture);

        void setSizeInSpriteMap(int w, int h);
        void setPositionInSpriteMap(int x, int y);

        void setRowsColsInSpriteMap(int rows, int cols);
        void setAnimationTime(float time);

        void update() override;
        void render() override;
};
