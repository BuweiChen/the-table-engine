// Camera.h
#pragma once

#include "component.h"
#include "vec2.h"

/**
 * @class Camera
 * @brief Manages the camera's view in a game, handling its position in the world space.
 *
 * The Camera class extends Component, allowing it to be attached to game objects and manage
 * the view based on the game object's transformations or other logic.
 */
class Camera : public Component {
public:
    /**
     * Constructor for the Camera class.
     */
    Camera();

    /**
     * Destructor for the Camera class.
     */
    ~Camera();

    /**
     * Updates the camera's position and behavior. This should be called each frame.
     */
    void update();

    /**
     * Gets the current world position of the camera.
     * @return The current world position as a Vec2.
     */
    Vec2 getWorldPosition();

    /**
     * Sets the world position of the camera.
     * @param x The x-coordinate of the new world position.
     * @param y The y-coordinate of the new world position.
     */
    void setWorldPosition(float x, float y);

private:
    Vec2 m_worldPosition; ///< Stores the world position of the camera.
};
