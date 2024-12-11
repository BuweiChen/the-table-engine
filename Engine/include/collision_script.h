/**
 * @file CollisionScript.h
 * @brief Handles collision logic for game objects.
 *
 * This script is used to attach collision logic to game objects. It checks
 * for collisions and performs necessary actions when a collision is detected.
 */

#include "script.h"
#include "collide.h"

/**
 * @class CollisionScript
 * @brief Script to manage collisions between game objects.
 *
 * Inherits from the Script class and utilizes the Collide component to handle
 * collisions.
 */
class CollisionScript : public Script {
private:
    bool m_collide; /**< Flag to track collision state */

public:
    /**
     * @brief Constructs a new Collision Script object.
     * 
     * Initializes the collision flag to false.
     */
    CollisionScript();

    /**
     * @brief Updates the collision status of the associated game object.
     * 
     * This method is called once per frame and checks for any collisions that
     * involve the game object this script is attached to.
     */
    void update() override;

    /**
     * @brief Renders collision-related visuals if necessary.
     * 
     * This method is called once per frame after update(), if there is a need
     * to render visual cues related to collision (like debug outlines).
     */
    void render() override;
};
