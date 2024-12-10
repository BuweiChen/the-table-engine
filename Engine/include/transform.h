#pragma once

/**
 * @file transform.h
 * @brief Provides the Transform component for positioning and sizing game objects.
 *
 * This component allows game objects to manage their positions and sizes within the world and relative to the screen.
 */

#include "component.h"
#include "vec2.h"
#include "gameobject.h"

#include "SDL2/SDL.h"

/**
 * @class Transform
 * @brief Component for handling the transformation of game objects.
 *
 * This class manages both the world and screen transformations of game objects,
 * allowing them to be positioned and sized accurately in the game world.
 */
class Transform : public Component {
    private:
        SDL_Rect* mTransform; ///< Holds position and size relative to the screen.
        Vec2 mPosition; ///< Position in world space.
        Vec2 mSize; ///< Size in world space.

    public:
        /**
         * @brief Default constructor.
         */
        Transform();

        /**
         * @brief Constructor that initializes the Transform with position.
         * @param x Initial x-coordinate of the world position.
         * @param y Initial y-coordinate of the world position.
         */
        Transform(int x, int y);

        /**
         * @brief Destructor.
         */
        ~Transform();

        /**
         * @brief Get the SDL_Rect describing the position and size on the screen.
         * @return Pointer to an SDL_Rect struct representing the screen rectangle.
         */
        SDL_Rect* getScreenRect();

        /**
         * @brief Get the world space position of the Transform.
         * @return A Vec2 object representing the world position.
         */
        Vec2 getWorldPosition();

        /**
         * @brief Get the screen space position calculated from world space.
         * @return A Vec2 object representing the screen position.
         */
        Vec2 getScreenPosition();

        /**
         * @brief Get the size of the Transform in screen space.
         * @return A Vec2 object representing the screen size.
         */
        Vec2 getScreenSize();

        /**
         * @brief Set the world space position of the Transform.
         * @param x New x-coordinate of the world position.
         * @param y New y-coordinate of the world position.
         */
        void setWorldPosition(float x, float y);

        /**
         * @brief Set the world space position of the Transform using a Vec2.
         * @param pos Vec2 representing the new world position.
         */
        void setWorldPosition(Vec2 pos);

        /**
         * @brief Update the world position by a delta value.
         * @param dx Change in the x-coordinate.
         * @param dy Change in the y-coordinate.
         */
        void updateWorldPosition(float dx, float dy);

        /**
         * @brief Update the world position by a delta position.
         * @param dpos Vec2 representing the change in position.
         */
        void updateWorldPosition(Vec2 dpos);

        /**
         * @brief Set the world space size of the Transform.
         * @param w Width in world space.
         * @param h Height in world space.
         */
        void setWorldSize(float w, float h);

        /**
         * @brief Set the world space size of the Transform using a Vec2.
         * @param size Vec2 representing the new size in world space.
         */
        void setWorldSize(Vec2 size);

        /**
         * @brief Render function for the Transform component, handling visual updates.
         */
        void render();
};
