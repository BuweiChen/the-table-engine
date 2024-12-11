/**
 * @file PlayerInputScript.h
 * @brief Script for handling player input in the game.
 *
 * This script is attached to the player game object and handles the input for
 * player movements and actions such as firing. It also tracks the number of keys
 * collected by the player.
 */

#pragma once 

#include "script.h"

/**
 * @class PlayerInputScript
 * @brief Handles player interactions and movements based on game input.
 *
 * PlayerInputScript controls how the player responds to keyboard inputs, managing
 * actions such as moving at a defined speed and firing at a controlled rate.
 */
class PlayerInputScript : public Script {
private:
    int m_fireRatePerSecond = 5; ///< Fire rate of the player in shots per second.
    int m_lastFireTimeInMs = 0; ///< Timestamp of the last fire to regulate shooting frequency.

    float m_playerSpeed = 6; ///< Speed at which the player moves.
    int m_keysCollected = 0; ///< Number of keys the player has collected.

public:
    /**
     * @brief Constructor for PlayerInputScript.
     * Initializes the script with default values for player speed and fire rate.
     */
    PlayerInputScript();

    /**
     * @brief Retrieves the number of keys collected by the player.
     * 
     * @return int The total number of keys collected.
     */
    int getKeysCollected();

    /**
     * @brief Updates player state based on input.
     * 
     * This method checks for player inputs and updates the player's position and actions
     * such as firing based on the input and predefined conditions like fire rate.
     */
    void update() override;
};
