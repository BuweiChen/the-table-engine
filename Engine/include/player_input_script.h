// player_input_script.h
/**
 * @file PlayerInputScript.h
 * @brief Script for handling player input in the game.
 *
 * This script is attached to the player game object and handles the input for
 * player movements and actions such as firing. It also tracks the number of keys
 * collected by the player and manages animation states.
 */

#pragma once 

#include "script.h"

/**
 * @class PlayerInputScript
 * @brief Handles player interactions, movements, and animation states based on game input.
 *
 * PlayerInputScript controls how the player responds to keyboard inputs, managing
 * actions such as moving at a defined speed and firing at a controlled rate.
 * It also manages the player's animation states based on their current action.
 */
class PlayerInputScript : public Script {
public:
    /**
     * @enum AnimationState
     * @brief Defines the possible animation states for the player.
     */
    enum AnimationState {
        IDLE = 0,   ///< Player is standing still
        RUN = 1,    ///< Player is moving
        DEATH = 2   ///< Player has died
    };

private:
    int m_fireRatePerSecond = 5;    ///< Fire rate of the player in shots per second.
    int m_lastFireTimeInMs = 0;      ///< Timestamp of the last fire to regulate shooting frequency.
    float m_playerSpeed = 6;         ///< Speed at which the player moves.
    int m_keysCollected = 0;         ///< Number of keys the player has collected.
    AnimationState m_currentState = IDLE;  ///< Current animation state of the player.

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
     * This method checks for player inputs and updates the player's position, actions,
     * and animation states based on the input and current game state.
     */
    void update() override;
};