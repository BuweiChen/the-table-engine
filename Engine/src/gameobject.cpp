#include <iostream>

#include "gameobject.h"
#include "texture.h"

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

std::string GameObject::getId() {
    return m_id;
}

std::string GameObject::getTag() {
    return m_tag;
}

SceneNode* GameObject::getSceneNode() {
    return m_sceneNode;
}

void GameObject::setSceneNode(SceneNode* sceneNode) {
    m_sceneNode = sceneNode;
}

void GameObject::input() {
    for (auto component : m_components) {
        component->input();
    }
    for (auto script : m_scripts) {
        script->input();
    }
}

void GameObject::update() {
    for (auto component : m_components) {
        component->update();
    }
    for (auto script : m_scripts) {
        script->update();
    }
}

void GameObject::render() {
    for (auto component : m_components) {
        component->render();
    }
    for (auto script : m_scripts) {
        script->render();
    }
}
