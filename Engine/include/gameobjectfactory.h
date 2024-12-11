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

    /**
     * @brief Creates a customized enemy warrior object with specific texture and animations.
     *
     * @param path Texture file path.
     * @param row Number of rows in the sprite sheet.
     * @param col Number of columns in the sprite sheet.
     * @param animationTime Duration of each animation frame.
     * @param pos_x Initial x-position of the enemy.
     * @param pos_y Initial y-position of the enemy.
     * @param size_x Width of the enemy in the game world.
     * @param size_y Height of the enemy in the game world.
     * @return GameObject* Pointer to the newly created customized enemy warrior.
     */
    static GameObject* createEnemyWarriorCustom(std::string path, int row, int col, float animationTime, int pos_x, int pos_y, int size_x, int size_y);

    /**
     * @brief Creates a basic tile object.
     *
     * @return GameObject* Pointer to the newly created tile object.
     */
    static GameObject* createTile1();

    /**
     * @brief Creates a customized tile object with specific texture.
     *
     * @param path Texture file path.
     * @param pos Position of the tile in the game world.
     * @param size Size of the tile.
     * @param sprite_size Size of the tile on the sprite sheet.
     * @param sprite_pos Position of the tile on the sprite sheet.
     * @return GameObject* Pointer to the newly created customized tile.
     */
    static GameObject* createTileCustom(std::string path, Vec2 pos, Vec2 size, Vec2 sprite_size, Vec2 sprite_pos);

    /**
     * @brief Creates a customized wall object with specific texture.
     *
     * @param path Texture file path.
     * @param pos Position of the wall in the game world.
     * @param size Size of the wall.
     * @param sprite_size Size of the wall on the sprite sheet.
     * @param sprite_pos Position of the wall on the sprite sheet.
     * @return GameObject* Pointer to the newly created customized wall.
     */
    static GameObject* createWallCustom(std::string path, Vec2 pos, Vec2 size, Vec2 sprite_size, Vec2 sprite_pos);

    /**
     * @brief Creates a customized table object with specific texture.
     *
     * @param path Texture file path.
     * @param pos Position of the table in the game world.
     * @param size Size of the table.
     * @param sprite_size Size of the table on the sprite sheet.
     * @param sprite_pos Position of the table on the sprite sheet.
     * @return GameObject* Pointer to the newly created customized table.
     */
    static GameObject* createTableCustom(std::string path, Vec2 pos, Vec2 size, Vec2 sprite_size, Vec2 sprite_pos);

    /**
     * @brief Creates a key object.
     *
     * @return GameObject* Pointer to the newly created key object.
     */
    static GameObject* createKey();

    /**
     * @brief Creates a crosshair object.
     *
     * @return GameObject* Pointer to the newly created crosshair object.
     */
    static GameObject* createCrosshair();
};
