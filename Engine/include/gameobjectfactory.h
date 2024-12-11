/**
 * @file GameObjectFactory.h
 * @brief Factory class for creating game objects.
 *
 * This class provides static methods for creating various types of game objects.
 * Each method returns a pointer to a newly created GameObject that can be used
 * directly in the game.
 */

#include "gameobject.h"
#include <string>

/**
 * @class GameObjectFactory
 * @brief Factory for constructing different types of game objects.
 *
 * GameObjectFactory provides a set of static methods that initialize game objects,
 * setting them up with initial configurations and returning them for use in the game.
 */
class GameObjectFactory {
public:
    /**
     * @brief Creates a test player object.
     *
     * @return GameObject* Pointer to the newly created player object.
     */
    static GameObject* createPlayerTest();

    /**
     * @brief Creates a bow object.
     *
     * @return GameObject* Pointer to the newly created bow object.
     */
    static GameObject* createBow();

    /**
     * @brief Creates an arrow object with specified dynamics.
     *
     * @param dx The change in the arrow's x-position per update.
     * @param dy The change in the arrow's y-position per update.
     * @return GameObject* Pointer to the newly created arrow object.
     */
    static GameObject* createArrow(int dx, int dy);

    /**
     * @brief Creates an enemy warrior object.
     *
     * @return GameObject* Pointer to the newly created enemy warrior object.
     */
    static GameObject* createEnemyWarrior();

    /**
     * @brief Creates a basic tile object.
     *
     * @return GameObject* Pointer to the newly created tile object.
     */
    static GameObject* createTile1();

    /**
     * @brief Creates a key object.
     *
     * @return GameObject* Pointer to the newly created key object.
     */
    static GameObject* createKey();
};
