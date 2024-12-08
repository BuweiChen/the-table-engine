#include <vector>
#include <functional>
#include <iostream>

#include "scene.h"
#include "gameobject.h"

SceneNode::SceneNode(GameObject* gameObject) {
    m_gameObject = gameObject;
    if (m_gameObject != nullptr) {
        m_gameObject->setSceneNode(this);
    }
    m_parent = nullptr;
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

void SceneNode::addChild(GameObject* child) {
    if (child == nullptr) return;

    SceneNode* childNode = new SceneNode(child);
    m_children.push_back(childNode);
    childNode->m_parent = this;
}

std::vector<SceneNode*> SceneNode::getChildren() {
    return m_children;
}

SceneNode* SceneNode::getParent() {
    return m_parent;
}

GameObject* SceneNode::getGameObject() {
    return m_gameObject;
}

SceneTree::SceneTree() {
    m_root = new SceneNode(nullptr);
}

SceneTree::~SceneTree() {
    delete m_root;
}

void SceneTree::addChild(GameObject* child) {
    m_root->addChild(child);
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
    std::vector<GameObject*> taggedGameObjects;
    traverseTree(m_root, [&taggedGameObjects, tag](SceneNode* node) {
        if (node && node->getGameObject() && node->getGameObject()->getTag() == tag) {
            taggedGameObjects.push_back(node->getGameObject());
        }
    });
    return taggedGameObjects;
}
