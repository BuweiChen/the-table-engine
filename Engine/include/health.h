#pragma once
#include "component.h"

/**
 * @file health.h
 * @brief Defines the Health class, a component for managing the health of game objects.
 *
 * This file declares the Health class, which is used to track and manage the health status
 * of game entities such as players and enemies. It offers methods to modify and retrieve
 * the current health state, supporting game mechanics involving damage and healing.
 */

/**
 * @class Health
 * @brief A component for managing health of game objects.
 *
 * The Health class extends the Component class and provides mechanisms to manage the
 * health of game objects. It allows setting, adjusting, and querying the health status,
 * facilitating the implementation of game rules related to life or vitality of characters
 * and other entities within the game.
 */
class Health : public Component {
    private:
        int m_currentHealth; ///< Current health of the game object.

    public:
        /**
         * @brief Constructor that initializes the health component.
         */
        Health();

        /**
         * @brief Destructor for the health component.
         */
        ~Health();

        /**
         * @brief Retrieves the current health of the game object.
         * @return Integer representing the current health.
         */
        int getHealth() const;

        /**
         * @brief Updates the health by a specified amount.
         * @param amount The amount to add to the current health (can be negative for damage).
         */
        void updateHealth(int amount);
};
