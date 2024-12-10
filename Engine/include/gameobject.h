#pragma once
 
#include <atomic>
#include <vector>

#include "component.h"
#include "script.h"
#include "scene.h"

#include "SDL2/SDL.h"

/**
 * @class GameObject
 * @brief Core class representing an entity in the game world.
 * 
 * GameObject serves as the base class for all game entities. It manages components
 * and scripts, handles lifecycle events (input, update, render), and maintains
 * relationships within the scene hierarchy.
 */
class GameObject {
    friend class SceneNode;
    
    private:
        std::string m_id;   ///< Unique identifier for the GameObject
        std::string m_tag;  ///< Category identifier (e.g., "Enemy", "Projectile")

        std::vector<Component*> m_components;  ///< List of attached components
        std::vector<Script*> m_scripts;       ///< List of attached scripts

        SceneNode* m_sceneNode;  ///< Node in the scene graph hierarchy

        /**
         * @brief Destructor that cleans up the GameObject and its SceneNode
         */
        ~GameObject();

    public:
        /**
         * @brief Constructs a new GameObject with the specified tag
         * @param tag Category identifier for the object
         */
        GameObject(std::string tag);

        /**
         * @brief Gets the unique identifier of the GameObject
         * @return std::string The GameObject's ID
         */
        std::string getId();

        /**
         * @brief Gets the tag identifier of the GameObject
         * @return std::string The GameObject's tag
         */
        std::string getTag();

        /**
         * @brief Gets a component of the specified type
         * @tparam T The type of component to retrieve
         * @return T* Pointer to the component, or nullptr if not found
         */
        template <typename T>
        T* getComponent();

        /**
         * @brief Adds a component to the GameObject
         * @tparam T The type of component to add
         * @param component Pointer to the component instance
         */
        template <typename T>
        void addComponent(T* component);
        
        /**
         * @brief Gets a script of the specified type
         * @tparam T The type of script to retrieve
         * @return T* Pointer to the script, or nullptr if not found
         */
        template <typename T>
        T* getScript();

        /**
         * @brief Adds a script to the GameObject
         * @tparam T The type of script to add
         * @param script Pointer to the script instance
         */
        template <typename T>
        void addScript(T* script);

        /**
         * @brief Gets the SceneNode associated with this GameObject
         * @return SceneNode* Pointer to the SceneNode
         */
        SceneNode* getSceneNode();

        /**
         * @brief Sets the SceneNode for this GameObject
         * @param sceneNode Pointer to the SceneNode
         */
        void setSceneNode(SceneNode* sceneNode);

        /**
         * @brief Gets all child GameObjects
         * @return std::vector<GameObject*> List of child GameObjects
         */
        std::vector<GameObject*> getChildren();

        /**
         * @brief Processes input for this GameObject and its components
         */
        void input();

        /**
         * @brief Updates this GameObject and its components
         */
        void update();

        /**
         * @brief Renders this GameObject and its components
         */
        void render();
};

template <typename T>
T* GameObject::getComponent() {
    for (auto component : m_components) {
        if (dynamic_cast<T*>(component) != nullptr) {
            return static_cast<T*>(component);
        }
    }
    return nullptr;
}

template <typename T>
void GameObject::addComponent(T* component) {
    auto base_component = static_cast<Component*>(component);
    GameObject::m_components.push_back(base_component);
    component->setOwner(this);
}

template <typename T>
T* GameObject::getScript() {
    for (auto script : m_scripts) {
        if (dynamic_cast<T*>(script) != nullptr) {
            return static_cast<T*>(script);
        }
    }
    return nullptr;
}

template <typename T>
void GameObject::addScript(T* script) {
    auto base_script = static_cast<Script*>(script);
    m_scripts.push_back(base_script);
    base_script->setOwner(this);
}
