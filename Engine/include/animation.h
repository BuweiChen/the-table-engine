#pragma once

/**
 * @file animation.h
 * @brief Defines the Animation class for handling sprite animations.
 */

#include "texture.h"

/**
 * @class Animation
 * @brief Component to handle animation of game objects. Derived from Texture.
 *
 * Animation extends the Texture class to provide functionalities for sprite animations.
 * It allows for setting the number of rows and columns in the sprite sheet, the total
 * animation time, and the current frame of animation. It also provides methods to start,
 * pause, and resume the animation, as well as to set a specific frame of animation.
 * The update method is used to advance the animation frame based on the elapsed time.
 * The render method is inherited from Texture and is used to render the current frame.
 */
class Animation : public Texture {
protected:
    int m_rows = 1;        ///< Number of rows in the sprite sheet
    int m_cols = 1;        ///< Number of columns in the sprite sheet
    float m_time = 1.0f;   ///< Total animation time in seconds
    int m_numFrames = 1;   ///< Total number of frames
    int m_msPerFrame;      ///< Milliseconds per frame
    
    bool m_isPlaying = true;   ///< Whether the animation is currently playing
    int m_currentFrame = 0;    ///< Current frame of animation
    int m_startTime = 0;       ///< Time when animation started/resumed
    int m_pausedTime = 0;      ///< Time when animation was paused

public:
    /**
     * @brief Default constructor.
     */
    Animation();

    /**
     * @brief Constructs an Animation with an associated SDL_Texture.
     */
    Animation(SDL_Texture* texture);

    /**
     * @brief Get the number of rows
     * @return int 
     */
    int getRows();

    /**
     * @brief Get the number of columns
     * @return int 
     */
    int getCols();

    /**
     * @brief Get the total number of frames
     * @return int 
     */
    int getNumFrames();

    /**
     * @brief Sets whether the animation should start playing automatically.
     * @param autoplay True to start playing immediately, false to start paused
     */
    void setAutoPlay(bool autoplay);

    /**
     * @brief Sets the number of rows and columns in the sprite map.
     */
    void setRowsColsInSpriteMap(int rows, int cols);

    /**
     * @brief Sets the total time for the animation cycle.
     */
    void setAnimationTime(float time);

    /**
     * @brief Starts or resumes the animation.
     */
    void play();

    /**
     * @brief Pauses the animation at current frame.
     */
    void pause();

    /**
     * @brief Sets a specific frame of animation.
     * @param frame The frame number to display (0-based)
     */
    void setFrame(int frame);

    /**
     * @brief Gets the current frame number.
     * @return Current frame number (0-based)
     */
    int getCurrentFrame() const { return m_currentFrame; }

    /**
     * @brief Checks if animation is currently playing.
     * @return True if animation is playing, false if paused
     */
    bool isPlaying() const { return m_isPlaying; }

    /**
     * @brief Updates the animation state.
     */
    void update() override;
};