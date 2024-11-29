#include "gameobject.h"

std::atomic<uint64_t> GameObject::m_totalObjects = 0;
std::atomic<uint64_t> GameObject::m_aliveObjects = 0;

GameObject::GameObject(std::string tag) {
    m_tag = tag;
    m_id = std::to_string(GameObject::m_totalObjects++);

    m_aliveObjects++;
}

GameObject::~GameObject() {
    m_aliveObjects--;
}

std::string GameObject::GetId() {
    return m_id;
}

std::string GameObject::GetTag() {
    return m_tag;
}

void GameObject::Input() {
    for (auto component : m_components) {
        component->Input();
    }
    for (auto script : m_scripts) {
        script->Input();
    }
}

void GameObject::Update() {
    for (auto component : m_components) {
        component->Update();
    }
    for (auto script : m_scripts) {
        script->Update();
    }
}

void GameObject::Render() {
    for (auto component : m_components) {
        component->Render();
    }
    for (auto script : m_scripts) {
        script->Render();
    }
}
