#pragma once
#include "component.h"

/**
 * @file health.h
 * @brief Defines the health class, a component for managing health of enemies and players.
 *
 * This component provides functionalities and for managing health of game
 * 
 */

/**
 * @class health
 * @brief Component to handle collisions between game objects.
 *
 * Collide uses SDL_Rect structures to define bounding boxes for collision detection and response.
 * It integrates with the game object's position and allows dynamic adjustment of the collision
 * box based on the game object's movements and interactions.
 */

class Health: public Component {
    private:
        int m_currentHealth;

    public:
        Health();

        ~Health();

        int getHealth();

        void updateHealth(int amount);    
};
