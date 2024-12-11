/**
 * @file EnemyAIScript.h
 * @brief Manages the behavior of an enemy in the game.
 *
 * This script handles the artificial intelligence for an enemy character,
 * controlling its movements and interactions within the game world.
 */

#include "script.h"

/**
 * @class EnemyAIScript
 * @brief Script to manage enemy artificial intelligence.
 *
 * Inherits from the Script class to define specific behaviors for enemy
 * characters, like movement speed and decision-making processes.
 */
class EnemyAIScript : public Script {
private:
    float m_speed = 2; /**< Speed of the enemy, controls how fast it moves */

public:
    /**
     * @brief Constructs a new Enemy AI Script object.
     * 
     * Sets the initial speed of the enemy AI.
     */
    EnemyAIScript();

    /**
     * @brief Updates the behavior of the enemy each frame.
     * 
     * This method is called once per frame and should include logic to determine
     * the enemy's actions based on its surroundings and internal state.
     */
    void update() override;

    /**
     * @brief Renders the enemy AI behavior.
     * 
     * This method is called once per frame after the update method, and should
     * include any rendering logic specific to the enemy AI.
     */
    void render() override;
};
