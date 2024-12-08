#pragma once
 
#include <atomic>
#include <vector>

#include "component.h"
#include "script.h"
#include "scene.h"

#include "SDL2/SDL.h"

class GameObject {
    private:
        std::string m_id; // unique identifier 
        std::string m_tag; // tag identifier e.g. "Enemy", "Projectile"

        static std::atomic<uint64_t> m_totalObjects;
        static std::atomic<uint64_t> m_aliveObjects;

        std::vector<Component*> m_components;
        std::vector<Script*> m_scripts;
        
        SceneNode* m_sceneNode;

    public:
        GameObject(std::string tag);
        ~GameObject();

        std::string getId();
        std::string getTag();

        template <typename T>
        T* getComponent();
        template <typename T>
        void addComponent(T* component);
        
        template <typename T>
        T* getScript();
        template <typename T>
        void addScript(T* script);

        SceneNode* getSceneNode();
        void setSceneNode(SceneNode* sceneNode);

        std::vector<GameObject*> getChildren();

        void input();
        void update();
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
