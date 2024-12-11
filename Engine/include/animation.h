#pragma once

/**
 * @file animation.h
 * @brief Defines the Animation component for managing sprite animations.
 *
 * This file provides the definitions necessary to manage sprite sheet animations,
 * extending the basic Texture component with animation capabilities.
 */

#include "texture.h"

/**
 * @class Animation 
 * @brief Manages sprite sheet animations.
 *
 * The Animation class extends Texture to provide sprite sheet animation capabilities,
 * including frame timing and sprite sheet coordinate management.
 */
class Animation : public Texture {
    protected:
        SDL_Rect* m_spriteBox;     ///< Defines the full bounding box of the sprite in the sprite map.
        SDL_Rect* m_spriteClip;    ///< Defines the section of the sprite box rendered per animation frame.
        int m_rows, m_cols;        ///< The number of rows and columns in the sprite map.
        float m_time;              ///< Total time in seconds to render the entire animation.

        int m_numFrames;    ///< Number of frames in the animation.
        int m_msPerFrame;   ///< Milliseconds per frame of animation.

    public:
        /**
         * @brief Default constructor.
         */
        Animation();

        /**
         * @brief Constructs an Animation with an associated SDL_Texture.
         * @param texture Pointer to the SDL_Texture to be managed.
         */
        Animation(SDL_Texture* texture);

        /**
         * @brief Destructor.
         */
        virtual ~Animation();

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

        int getMsPerFrame() const { return m_msPerFrame; }
        void setMsPerFrame(int msPerFrame) { m_msPerFrame = msPerFrame; }

        /**
         * @brief Updates the animation state.
         */
        virtual void update() override;

        /**
         * @brief Renders the current animation frame.
         */
        virtual void render() override;
};