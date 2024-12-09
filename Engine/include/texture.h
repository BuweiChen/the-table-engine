#pragma once

#include "SDL2/SDL.h"
#include "transform.h"

class Texture : public Component {
    private:
        SDL_Texture* m_texture;
        SDL_Renderer* m_renderer;

        SDL_Rect* m_spriteBox; // section of sprite map rendered for specifc game object
        SDL_Rect* m_spriteClip; // section of sprite box rendered per animation frame
        int m_rows, m_cols; // rows and columns in sprite map
        float m_time; // total time to render entire animation

        bool m_flipHorizontal = false;
        bool m_flipVertical = false;

        int m_numFrames;
        int m_msPerFrame;


    public:
        Texture();
        Texture(SDL_Texture* texture);

        SDL_Texture* getTexture();
        void setTexture(SDL_Texture* texture);

        void setSizeInSpriteMap(int w, int h);
        void setPositionInSpriteMap(int x, int y);

        void setRowsColsInSpriteMap(int rows, int cols);
        void setAnimationTime(float time);

        void setFlipHorizontal(bool flip);
        void setFlipVertical(bool flip);

        void update() override;
        void render() override;
};
