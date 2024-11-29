#pragma once

#include <vector>
#include <atomic>

#include "component.h"
#include "script.h"

#include "SDL2/SDL.h"

class GameObject {
    private:
        std::string m_id; // unique identifier 
        std::string m_tag; // tag identifier e.g. "Enemy", "Projectile"

        static std::atomic<uint64_t> m_totalObjects;
        static std::atomic<uint64_t> m_aliveObjects;

        std::vector<Component*> m_components;
        std::vector<Script*> m_scripts;

    public:
        GameObject(std::string tag);
        ~GameObject();

        std::string GetId();
        std::string GetTag();

        template <typename T>
        T* GetComponent();
        template <typename T>
        void AddComponent(T* component);
        
        template <typename T>
        void AddScript(T* script);

        void Input();
        void Update();
        void Render();
};

template <typename T>
T* GameObject::GetComponent() {
    for (auto component : m_components) {
        if (dynamic_cast<T*>(component) != nullptr) {
            return static_cast<T*>(component);
        }
    }
    return nullptr;
}

template <typename T>
void GameObject::AddComponent(T* component) {
    auto base_component = static_cast<Component*>(component);
    GameObject::m_components.push_back(base_component);
    component->SetOwner(this);
}

template <typename T>
void GameObject::AddScript(T* script) {
    auto base_script = static_cast<Script*>(script);
    m_scripts.push_back(base_script);
    script->SetOwner(this);
}
