// animationsmanager.h
#pragma once

#include "texture.h"
#include "animation.h"
#include <vector>
#include <string>

/**
 * @class AnimationsManager
 * @brief Manages a collection of animations for a game entity, with functionality to play, pause, and switch between animations.
 *
 * AnimationsManager extends Texture, allowing it to directly control the rendering of animations
 * based on the Texture properties.
 */
class AnimationsManager : public Texture {
protected:
    std::vector<Animation*> m_animations; ///< Stores pointers to Animation objects.
    size_t m_currentAnimation = 0;        ///< Index of the currently active animation.
    bool m_isPlaying = true;              ///< Flag to check if the animation is currently playing.

public:
    AnimationsManager();
    ~AnimationsManager();

    /**
     * Adds a new Animation object to the manager.
     * @param animation Pointer to the Animation to add.
     * @return The index of the added animation within the manager.
     */
    int addAnimation(Animation* animation);

    /**
     * Creates a new animation directly from texture details and adds it to the manager.
     * @param texture Pointer to the SDL_Texture resource.
     * @param rows Number of rows in the sprite sheet.
     * @param cols Number of columns in the sprite sheet.
     * @param time Duration of each animation frame.
     * @return The index of the created animation.
     */
    int createAnimation(SDL_Texture* texture, int rows, int cols, float time);

    /**
     * Sets the currently active animation.
     * @param index Index of the animation to make active.
     */
    void setCurrentAnimation(size_t index);

    /**
     * Retrieves the index of the currently active animation.
     * @return Index of the current animation.
     */
    size_t getCurrentAnimation() const;

    /**
     * Gets the Animation object of the currently active animation.
     * @return Pointer to the current Animation object.
     */
    Animation* getCurrentAnimationObject();

    /**
     * Starts or resumes playing the current animation.
     */
    void play();

    /**
     * Pauses the current animation.
     */
    void pause();

    /**
     * Sets the frame number of the current animation.
     * @param frame Frame number to set.
     */
    void setFrame(int frame);

    /**
     * Gets the current frame number of the animation.
     * @return Current frame number.
     */
    int getCurrentFrame() const;

    /**
     * Checks if the animation is currently playing.
     * @return True if the animation is playing, false otherwise.
     */
    bool isPlaying() const;

    /**
     * Updates the current animation state. Should be called per frame.
     */
    void update() override;

    /**
     * Renders the current frame of the animation. Should be called per frame.
     */
    void render() override;

    // Overrides from Texture class
    void setTexture(SDL_Texture* texture) override;
    void setSizeInSpriteMap(int w, int h) override;
    void setPositionInSpriteMap(int x, int y) override;
    void setFlipHorizontal(bool flip) override;
    void setFlipVertical(bool flip) override;
    void setAngle(float angle) override;
};
