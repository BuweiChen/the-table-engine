#pragma once

#include "component.h"
#include "vec2.h"

#include "SDL2/SDL.h"

/**
 * @file collide.h
 * @brief Defines the Collide class, a component for managing collision detection and response.
 *
 * This component provides functionalities to manage collision boxes, detect collisions,
 * and adjust object movements to prevent overlapping with other collidable objects.
 */

/**
 * @class Collide
 * @brief Component to handle collisions between game objects.
 *
 * Collide uses SDL_Rect structures to define bounding boxes for collision detection and response.
 * It integrates with the game object's position and allows dynamic adjustment of the collision
 * box based on the game object's movements and interactions.
 */
class Collide: public Component {
private:
    SDL_Rect* mCollide; ///< The collision rectangle relative to the screen.

    float mOffsetX, mOffsetY; ///< Offset of the collider's position from the game object's transform position.
    
    /**
     * @brief Calculates the position of the collider for the next frame.
     * @param dx Horizontal displacement.
     * @param dy Vertical displacement.
     * @return A pointer to an SDL_Rect representing the next frame's collider position.
     */
    SDL_Rect* nextRect(float dx, float dy);

public:
    /**
     * @brief Constructor for the Collide component.
     */
    Collide();

    /**
     * @brief Destructor for the Collide component.
     */
    ~Collide();

    /**
     * @brief Gets the current collision rectangle.
     * @return A pointer to an SDL_Rect representing the current collision rectangle.
     */
    SDL_Rect* getRect();

    /**
     * @brief Retrieves the screen position of the collision rectangle.
     * @return A Vec2 object representing the screen position.
     */
    Vec2 getScreenPosition();

    /**
     * @brief Retrieves the size of the collision rectangle on the screen.
     * @return A Vec2 object representing the size of the collision rectangle.
     */
    Vec2 getScreenSize();

    /**
     * @brief Modifies velocities to prevent collision with another Collide component.
     * @param anotherCollide Pointer to another Collide component.
     * @param dx Reference to the horizontal velocity that may be modified.
     * @param dy Reference to the vertical velocity that may be modified.
     */
    void preventCollision(Collide* anotherCollide, float& dx, float& dy);

    /**
     * @brief Sets the offset of the collider from the transform's position.
     * @param x Horizontal offset.
     * @param y Vertical offset.
     */
    void setTransformOffset(int x, int y);
    
    /**
     * @brief Sets the screen position of the collider.
     * @param x Horizontal screen position.
     * @param y Vertical screen position.
     */
    void setScreenPosition(int x, int y);
    
    /**
     * @brief Sets the screen position of the collider using a Vec2 object.
     * @param pos Vec2 object representing the new position.
     */
    void setScreenPosition(Vec2 pos);
    
    /**
     * @brief Sets the size of the collider on the screen.
     * @param w Width of the collider.
     * @param h Height of the collider.
     */
    void setScreenSize(int w, int h);
    
    /**
     * @brief Sets the size of the collider on the screen using a Vec2 object.
     * @param size Vec2 object representing the new size.
     */
    void setScreenSize(Vec2 size);

    /**
     * @brief Checks if this collider is colliding with a given SDL_Rect.
     * @param rect Pointer to an SDL_Rect to check against.
     * @return True if colliding, false otherwise.
     */
    bool isColliding(SDL_Rect* rect);
    
    /**
     * @brief Checks if this collider is colliding with another Collide component.
     * @param collide Pointer to another Collide component to check against.
     * @return True if colliding, false otherwise.
     */
    bool isColliding(Collide* collide);

    /**
     * @brief Updates the collision state of the component.
     */
    void update();

    /**
     * @brief Renders the collision boundaries for debugging purposes.
     */
    void render();
};
