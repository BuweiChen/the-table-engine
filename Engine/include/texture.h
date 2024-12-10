#pragma once

/**
 * @file texture.h
 * @brief Defines the Texture component for managing textures in the Game Engine.
 *
 * This file provides the definitions necessary to manage textures and animations associated with game objects, 
 * handling sprite sheets, frame animations, and texture rendering.
 */

#include "SDL2/SDL.h"
#include "transform.h"

/**
 * @class Texture
 * @brief Manages texture assets, including sprite maps and animations.
 *
 * The Texture class is responsible for handling and rendering textures associated with game objects.
 * It supports animations by managing sprite sheets and the rendering of specific frames.
 */
class Texture : public Component {
    private:
        SDL_Texture* m_texture; ///< Pointer to the SDL_Texture object.
        SDL_Renderer* m_renderer; ///< Pointer to the SDL_Renderer object used for rendering the texture.

        SDL_Rect* m_spriteBox; ///< Defines the section of the sprite map rendered for a specific game object.
        SDL_Rect* m_spriteClip; ///< Defines the section of the sprite box rendered per animation frame.
        int m_rows, m_cols; ///< The number of rows and columns in the sprite map.
        float m_time; ///< Total time in seconds to render the entire animation.

        bool m_flipHorizontal = false; ///< Flag to flip the texture horizontally.
        bool m_flipVertical = false; ///< Flag to flip the texture vertically.

        int m_numFrames; ///< Number of frames in the animation.
        int m_msPerFrame; ///< Milliseconds per frame of animation.

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
         * @brief Retrieves the current SDL_Texture.
         * @return Pointer to the SDL_Texture being used.
         */
        SDL_Texture* getTexture();

        /**
         * @brief Sets the SDL_Texture to be managed.
         * @param texture Pointer to the new SDL_Texture.
         */
        void setTexture(SDL_Texture* texture);

        /**
         * @brief Sets the size of the sprite in the sprite map.
         * @param w Width of the sprite in the map.
         * @param h Height of the sprite in the map.
         */
        void setSizeInSpriteMap(int w, int h);

        /**
         * @brief Sets the position of the sprite in the sprite map.
         * @param x X-coordinate of the sprite in the map.
         * @param y Y-coordinate of the sprite in the map.
         */
        void setPositionInSpriteMap(int x, int y);

        /**
         * @brief Sets the number of rows and columns in the sprite map.
         * @param rows Number of rows in the sprite map.
         * @param cols Number of columns in the sprite map.
         */
        void setRowsColsInSpriteMap(int rows, int cols);

        /**
         * @brief Sets the total time for the animation cycle.
         * @param time Total time in seconds for the animation.
         */
        void setAnimationTime(float time);

        /**
         * @brief Sets whether the texture should be flipped horizontally.
         * @param flip True to flip horizontally, false otherwise.
         */
        void setFlipHorizontal(bool flip);

        /**
         * @brief Sets whether the texture should be flipped vertically.
         * @param flip True to flip vertically, false otherwise.
         */
        void setFlipVertical(bool flip);

        /**
         * @brief Updates the animation state of the texture.
         */
        void update() override;

        /**
         * @brief Renders the texture to the screen.
         */
        void render() override;
};
