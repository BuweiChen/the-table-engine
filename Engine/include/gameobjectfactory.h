/**
 * @file GameObjectFactory.h
 * @brief Factory class for creating game objects.
 *
 * This class provides static methods for creating various types of game objects.
 * Each method returns a pointer to a newly created GameObject that can be used
 * directly in the game.
 */

#include "gameobject.h"
#include "vec2.h"
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

    static GameObject* createEnemyWarriorCustom(std::string path, int row, int col, float animationTime, int pos_x, int pos_y, int size_x, int size_y);

    /**
     * @brief Creates a basic tile object.
     *
     * @return GameObject* Pointer to the newly created tile object.
     */
    static GameObject* createTile1();
    static GameObject* createTileCustom(std::string path, Vec2 pos, Vec2 size, Vec2 sprite_size, Vec2 sprite_pos);


    static GameObject* createWallCustom(std::string path, Vec2 pos, Vec2 size, Vec2 sprite_size, Vec2 sprite_pos);

    static GameObject* createTableCustom(std::string path, Vec2 pos, Vec2 size, Vec2 sprite_size, Vec2 sprite_pos);
    /**
     * @brief Creates a key object.
     *
     * @return GameObject* Pointer to the newly created key object.
     */
    static GameObject* createKey();
};
