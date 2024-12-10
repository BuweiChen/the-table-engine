#pragma once
 
#include <atomic>
#include <vector>
#include <string>

#include "component.h"
#include "script.h"
#include "scene.h"

#include "SDL2/SDL.h"

/**
 * @file gameobject.h
 * @brief Defines the GameObject class for managing game objects within the engine.
 *
 * This file contains the definition of the GameObject class, which acts as a container
 * for components and scripts that define the behavior and properties of objects in the game.
 */

/**
 * @class GameObject
 * @brief Represents an object in the game world, managing components and scripts.
 *
 * GameObjects are the primary elements within the game scene, capable of holding various components
 * and scripts that define their behavior, appearance, and interactions within the game world.
 */
class GameObject {
    friend class SceneNode;
    
    private:
        std::string m_id; ///< Unique identifier for the GameObject.
        std::string m_tag; ///< Tag identifier, useful for grouping or identifying objects like "Enemy", "Projectile".

        std::vector<Component*> m_components; ///< Stores all components attached to this GameObject.
        std::vector<Script*> m_scripts; ///< Stores all scripts attached to this GameObject.

        SceneNode* m_sceneNode; ///< Pointer to the SceneNode in the scene graph associated with this GameObject.

        /**
         * @brief Destructor for cleaning up resources.
         * Deletes the associated SceneNode to ensure proper cleanup of the GameObject.
         */
        ~GameObject();

    public:
        /**
         * @brief Constructs a GameObject with a specific tag.
         * @param tag The tag to identify or classify the GameObject.
         */
        GameObject(std::string tag);

        /**
         * @brief Retrieves the unique ID of the GameObject.
         * @return A string representing the unique identifier.
         */
        std::string getId();

        /**
         * @brief Retrieves the tag of the GameObject.
         * @return A string representing the tag.
         */
        std::string getTag();

        /**
         * @brief Retrieves a component of a specific type attached to this GameObject.
         * @return Pointer to the component, or nullptr if not found.
         */
        template <typename T>
        T* getComponent();

        /**
         * @brief Adds a component of a specific type to this GameObject.
         * @param component Pointer to the component to be added.
         */
        template <typename T>
        void addComponent(T* component);
        
        /**
         * @brief Retrieves a script of a specific type attached to this GameObject.
         * @return Pointer to the script, or nullptr if not found.
         */
        template <typename T>
        T* getScript();

        /**
         * @brief Adds a script of a specific type to this GameObject.
         * @param script Pointer to the script to be added.
         */
        template <typename T>
        void addScript(T* script);

        /**
         * @brief Retrieves the SceneNode associated with this GameObject.
         * @return Pointer to the SceneNode.
         */
        SceneNode* getSceneNode();

        /**
         * @brief Sets the SceneNode associated with this GameObject.
         * @param sceneNode Pointer to the SceneNode to be associated.
         */
        void setSceneNode(SceneNode* sceneNode);

        /**
         * @brief Retrieves all child GameObjects under this GameObject's SceneNode.
         * @return A vector of pointers to the child GameObjects.
         */
        std::vector<GameObject*> getChildren();

        /**
         * @brief Handles input for this GameObject.
         */
        void input();

        /**
         * @brief Updates this GameObject.
         */
        void update();

        /**
         * @brief Renders this GameObject.
         */
        void render();
};

// Template methods documentation would ideally appear here or in an accompanying .cpp file, 
// if used for template instantiation descriptions.
