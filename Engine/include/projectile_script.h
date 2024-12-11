/**
 * @file ProjectileScript.h
 * @brief Script for managing projectile movement within the game.
 *
 * This script handles the logic for moving projectiles like bullets or arrows
 * in a specified direction with a given velocity. It is attached to projectile
 * game objects to control their behavior after being fired.
 */

#pragma once

#include "script.h"

/**
 * @class ProjectileScript
 * @brief Controls the movement of a projectile.
 *
 * ProjectileScript updates the position of the projectile game object based on
 * initial velocities provided during its creation. This class ensures that the
 * projectile moves in a straight line with the specified velocity.
 */
class ProjectileScript : public Script {
private:
    float m_dx; ///< Horizontal velocity component of the projectile.
    float m_dy; ///< Vertical velocity component of the projectile.

public:
    /**
     * @brief Constructs a ProjectileScript with specified velocity components.
     * 
     * @param dx The horizontal component of the projectile's velocity.
     * @param dy The vertical component of the projectile's velocity.
     */
    ProjectileScript(float dx, float dy);

    /**
     * @brief Updates the position of the projectile based on its velocity.
     * 
     * This method calculates the new position of the projectile by adding the
     * velocity components to its current position, simulating movement.
     */
    void update() override;
};
