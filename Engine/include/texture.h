#pragma once

/**
 * @file texture.h
 * @brief Defines the Texture component for managing textures in the Game Engine.
 */

#include "SDL2/SDL.h"
#include "component.h"
#include "transform.h"

/**
 * @class Texture
 * @brief Component for managing textures in the game engine.
 * 
 */
class Texture : public Component {
protected:
    SDL_Texture* m_texture;    ///< Pointer to the SDL_Texture object
    SDL_Renderer* m_renderer;  ///< Pointer to the SDL_Renderer object
    SDL_Rect* m_spriteBox;     ///< Defines the full bounding box of the sprite
    SDL_Rect* m_spriteClip;    ///< Defines the section of the sprite to render

    bool m_flipHorizontal = false; ///< Flag to flip the texture horizontally
    bool m_flipVertical = false;   ///< Flag to flip the texture vertically
    float m_angle = 0.0f;          ///< Rotation angle in degrees

public:
    /**
     * @brief Default constructor.
     */
    Texture();

    /**
     * @brief Constructs a Texture with an associated SDL_Texture.
     * @param texture Pointer to the SDL_Texture to be managed.
     */
    Texture(SDL_Texture* texture);

    /**
     * @brief Gets the current texture.
     */
    SDL_Texture* getTexture();

    /**
     * @brief Sets the texture to be managed.
     */
    void setTexture(SDL_Texture* texture);

    /**
     * @brief Sets the size of the sprite in the sprite map.
     */
    void setSizeInSpriteMap(int w, int h);

    /**
     * @brief Sets the position of the sprite in the sprite map.
     */
    void setPositionInSpriteMap(int x, int y);

    /**
     * @brief Sets whether the texture should be flipped horizontally.
     */
    void setFlipHorizontal(bool flip);

    /**
     * @brief Sets whether the texture should be flipped vertically.
     */
    void setFlipVertical(bool flip);

    /**
     * @brief Sets the rotation angle for the texture.
     */
    void setAngle(float angle) { m_angle = angle; }

    /**
     * @brief Updates the texture state.
     */
    virtual void update() override;

    /**
     * @brief Renders the texture to the screen.
     */
    virtual void render() override;
};