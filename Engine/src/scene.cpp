#include <vector>
#include <functional>
#include <iostream>

#include "scene.h"
#include "health.h"
#include "gameobject.h"

// Scene Node

SceneNode::SceneNode(GameObject* gameObject) {
    m_gameObject = gameObject;
    if (m_gameObject != nullptr) {
        m_gameObject->setSceneNode(this);
    }
    m_parent = nullptr;
    m_isBackground = false;
}

SceneNode::~SceneNode() {
    // delete all children nodes
    for (auto child : m_children) {
        delete child;
    }
    // remove this node from parent's children list
    if (m_parent && !m_parent->m_children.empty()) {
        for (auto it = m_parent->m_children.begin(); it != m_parent->m_children.end(); ++it) {
            if (*it == this) {
                m_parent->m_children.erase(it);
                break;
            }
        }
    }
    // delete game object
    m_parent = nullptr;
    m_children.clear();
    delete m_gameObject;
}

void SceneNode::addChild(GameObject* child, bool isBackground) {
    if (child == nullptr) return;

    SceneNode* childNode = new SceneNode(child);
    childNode->setIsBackground(isBackground);
    m_children.push_back(childNode);
    childNode->m_parent = this;
}

const std::vector<SceneNode*> SceneNode::getChildren() {
    return m_children;
}

SceneNode* SceneNode::getParent() {
    return m_parent;
}

GameObject* SceneNode::getGameObject() {
    return m_gameObject;
}

bool SceneNode::readyToDestroy() {
    return m_destroy;
}

void SceneNode::setDestroy(bool destroy) {
    m_destroy = destroy;
}

bool SceneNode::isBackground() {
    return m_isBackground;
}

void SceneNode::setIsBackground(bool isBackground) {
    m_isBackground = isBackground;
}

// Scene Tree

SceneTree::SceneTree() {
    m_root = new SceneNode(nullptr);
}

SceneTree::~SceneTree() {
    delete m_root;
}

void SceneTree::addChild(GameObject* child, bool isBackground) {
    m_root->addChild(child, isBackground);
}

void SceneTree::traverseTree(std::function<void(SceneNode*)> callback) {
    traverseTree(m_root, callback);
}

void SceneTree::traverseTree(SceneNode* node, std::function<void(SceneNode*)> callback) {
    if (node == nullptr) return;

    callback(node);
    for (auto child : node->getChildren()) {
        traverseTree(child, callback);
    }
}

GameObject* SceneTree::findGameObjectById(std::string id) {
    GameObject* idGameObject = nullptr;
    traverseTree(m_root, [&idGameObject, id](SceneNode* node) {
        if (node && node->getGameObject() && node->getGameObject()->getId() == id) {
            idGameObject = node->getGameObject();
        }
    });
    return idGameObject;
}

std::vector<GameObject*> SceneTree::findGameObjectsByTag(std::string tag) {
    if (m_cachedGameObjects.find(tag) != m_cachedGameObjects.end()) {
        return {m_cachedGameObjects[tag]};
    }
    if (m_cachedGameObjectsInFrame.find(tag) != m_cachedGameObjectsInFrame.end()) {
        return m_cachedGameObjectsInFrame[tag];
    }

    std::vector<GameObject*> taggedGameObjects;
    traverseTree(m_root, [&taggedGameObjects, tag](SceneNode* node) {
        if (node && node->getGameObject() && node->getGameObject()->getTag() == tag) {
            taggedGameObjects.push_back(node->getGameObject());
        }
    });

    // cache specific game objects
    if (tag == "Player" || tag == "Bow") {
        m_cachedGameObjects[tag] = taggedGameObjects[0];
    }
    else
        m_cachedGameObjectsInFrame[tag] = taggedGameObjects;
        
    return taggedGameObjects;
}

std::vector<GameObject*>& SceneTree::findCachedGameObjectsInFrame(std::string tag) {
    return m_cachedGameObjectsInFrame[tag];
}

void SceneTree::resetCachedGameObjectsInFrame() {
    m_cachedGameObjectsInFrame.clear();
}

int SceneTree::gameStatus() {
    // check if player is dead
    auto players = SceneTree::findGameObjectsByTag("Player");
    auto health = players[0]->getComponent<Health>();
    if (health->getHealth() <= 0) {
        return -1;
    }
    // check if all enemies and keys are collected
    auto enemies = SceneTree::findGameObjectsByTag("Warrior");
    auto keys = SceneTree::findGameObjectsByTag("Key");
    if (enemies.empty() && keys.empty()) {
        return 1;
    }
    // game is still running
    return 0;
}