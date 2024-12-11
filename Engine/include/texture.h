#pragma once

/**
 * @file texture.h
 * @brief Defines the Texture component for managing textures in the Game Engine.
 */

#include "SDL2/SDL.h"
#include "component.h"
#include "transform.h"

class Texture : public Component {
protected:
    SDL_Texture* m_texture;    
    SDL_Renderer* m_renderer;  
    SDL_Rect* m_spriteBox;    
    SDL_Rect* m_spriteClip;    

    bool m_flipHorizontal = false;
    bool m_flipVertical = false;   
    float m_angle = 0.0f;         

public:
    Texture();
    Texture(SDL_Texture* texture);

    SDL_Texture* getTexture();
    virtual void setTexture(SDL_Texture* texture);
    virtual void setSizeInSpriteMap(int w, int h);
    virtual void setPositionInSpriteMap(int x, int y);
    virtual void setFlipHorizontal(bool flip);
    virtual void setFlipVertical(bool flip);
    virtual void setAngle(float angle);
    virtual void update() override;
    virtual void render() override;

    void setColorMod(const SDL_Color& color);

};
