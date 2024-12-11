#pragma once

/**
 * @file texture.h
 * @brief Defines the Texture component for managing textures within the Game Engine, encapsulating SDL texture operations and transformations.
 */

#include "SDL2/SDL.h"
#include "component.h"
#include "transform.h"

/**
 * @class Texture
 * @brief Component for handling textures in the game engine.
 *
 * The Texture class extends the Component class, providing specific functionalities
 * for texture management including handling sprite sheets, texture transformations,
 * and rendering operations.
 */
class Texture : public Component {
protected:
    SDL_Texture* m_texture;    ///< Pointer to the SDL_Texture object.
    SDL_Renderer* m_renderer;  ///< Pointer to the SDL_Renderer associated with this texture.
    SDL_Rect* m_spriteBox;     ///< Destination rectangle on the screen for rendering the texture.
    SDL_Rect* m_spriteClip;    ///< Source rectangle in the sprite sheet for slicing the texture.

    bool m_flipHorizontal = false; ///< Flag for horizontal flipping of the texture.
    bool m_flipVertical = false;   ///< Flag for vertical flipping of the texture.
    float m_angle = 0.0f;          ///< Rotation angle of the texture in degrees.

public:
    /**
     * @brief Default constructor for the Texture class, initializes an empty texture.
     */
    Texture();

    /**
     * @brief Constructor with texture initialization.
     * @param texture Pointer to an SDL_Texture to be managed.
     */
    Texture(SDL_Texture* texture);

    /**
     * @brief Retrieves the SDL_Texture object.
     * @return SDL_Texture* Pointer to the managed SDL_Texture object.
     */
    SDL_Texture* getTexture();

    /**
     * @brief Sets the SDL_Texture object.
     * @param texture Pointer to the new SDL_Texture to be managed.
     */
    virtual void setTexture(SDL_Texture* texture);

    /**
     * @brief Sets the size of the sprite in the sprite map.
     * @param w Width of the sprite in the sprite sheet.
     * @param h Height of the sprite in the sprite sheet.
     */
    virtual void setSizeInSpriteMap(int w, int h);

    /**
     * @brief Sets the position of the sprite in the sprite map.
     * @param x Horizontal position of the sprite in the sprite sheet.
     * @param y Vertical position of the sprite in the sprite sheet.
     */
    virtual void setPositionInSpriteMap(int x, int y);

    /**
     * @brief Sets horizontal flip status.
     * @param flip True to flip the texture horizontally, false otherwise.
     */
    virtual void setFlipHorizontal(bool flip);

    /**
     * @brief Sets vertical flip status.
     * @param flip True to flip the texture vertically, false otherwise.
     */
    virtual void setFlipVertical(bool flip);

    /**
     * @brief Sets the rotation angle of the texture.
     * @param angle Rotation angle in degrees.
     */
    virtual void setAngle(float angle);

    /**
     * @brief Updates texture properties, used mainly for animations or transformations.
     */
    virtual void update() override;

    /**
     * @brief Renders the texture to the screen based on current properties.
     */
    virtual void render() override;

    /**
     * @brief Sets the color modulation for the texture.
     * @param color SDL_Color structure containing the RGB values to modulate the texture.
     */
    void setColorMod(const SDL_Color& color);
};
