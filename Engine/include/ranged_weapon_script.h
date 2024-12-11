/**
 * @file RangedWeaponScript.h
 * @brief Script for managing the functionality of ranged weapons in the game.
 *
 * This script handles the input and update logic for ranged weapons, managing
 * shooting mechanics, fire rate control, and animation handling.
 */

#pragma once

#include "script.h"

/**
 * @class RangedWeaponScript
 * @brief Controls the behavior of ranged weapons such as bows or guns.
 *
 * RangedWeaponScript manages the shooting actions of weapons, checks the fire
 * rate to prevent shooting too frequently, and ensures that necessary
 * animations are played when shooting.
 */
class RangedWeaponScript : public Script {
private:
    bool m_shoot; ///< Flag to indicate whether the weapon should shoot.
    int m_lastFireTimeInMs; ///< Timestamp of the last shooting action in milliseconds.
    int m_fireRatePerSecond; ///< Allowed number of shots per second to control shooting frequency.
    bool m_wasSpacePressed; ///< Tracks if the space key was pressed, typically used for shooting.
    bool m_animationPlayed; ///< Ensures that the shooting animation plays correctly.

public:
    /**
     * @brief Constructs a RangedWeaponScript with default or initial settings.
     *
     * Initializes control variables and state tracking for the ranged weapon.
     */
    RangedWeaponScript();

    /**
     * @brief Processes input to handle shooting actions.
     *
     * Checks for relevant user inputs, like key presses, to trigger shooting.
     * Ensures that shooting actions respect the defined fire rate.
     */
    void input() override;

    /**
     * @brief Updates the state of the weapon based on input and time constraints.
     *
     * Manages the timing and state changes required to control shooting frequency
     * and animation states. This method is called each frame of the game loop to
     * ensure responsive weapon behavior.
     */
    void update() override;
};
