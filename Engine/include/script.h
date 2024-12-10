#pragma once

/**
 * @file script.h
 * @brief Defines the Script class for attaching behavior to game objects.
 *
 * The Script class allows custom behaviors to be attached to game objects, 
 * providing hooks for input handling, updating state, and rendering.
 */

#include <string>

class GameObject; // Forward declaration to avoid circular dependency.

/**
 * @class Script
 * @brief Base class for scripting custom behaviors in game objects.
 *
 * Scripts are used to define interactive or autonomous behaviors for game objects.
 * They can handle input, update logic, and rendering specifics for the associated game object.
 */
class Script {
    public:
        std::string m_name; ///< Name of the script, useful for identification or debugging.
        GameObject* m_owner; ///< Pointer to the GameObject that owns this script.

        /**
         * @brief Default constructor, initializes an empty script.
         */
        Script();

        /**
         * @brief Constructs a Script with a specified name.
         * @param name Name of the script.
         */
        Script(std::string name);

        /**
         * @brief Virtual destructor to allow for cleanup in derived script classes.
         */
        virtual ~Script();

        /**
         * @brief Retrieves the name of the script.
         * @return The name of the script as a std::string.
         */
        std::string getName();

        /**
         * @brief Retrieves the owner GameObject of this script.
         * @return Pointer to the GameObject that owns this script.
         */
        GameObject* getOwner();

        /**
         * @brief Sets the owner of this script.
         * @param owner Pointer to the GameObject to be set as the owner of this script.
         */
        void setOwner(GameObject* owner);

        /**
         * @brief Virtual method for handling input. Should be overridden by derived classes.
         */
        virtual void input();

        /**
         * @brief Virtual method for updating the script's state. Should be overridden by derived classes.
         */
        virtual void update();

        /**
         * @brief Virtual method for rendering operations. Should be overridden by derived classes.
         */
        virtual void render();
};
