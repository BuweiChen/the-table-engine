#include "gameobject.h"
#include "transform.h"
#include "resourcemanager.h"
#include "texture.h"
#include "scenemanager.h"
#include "gameobjectfactory.h"

#include <iostream>

SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::setRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

SceneTree* SceneManager::getSceneTree() {
    return m_sceneTree;
}

void SceneManager::getNextScene() {
    ++m_currentSceneIndex;
    switch (m_currentSceneIndex) {
        case 1:
            m_sceneTree = createSceneTest1();
            break;
        default:
            m_sceneTree = nullptr;
            break;
    }
}

SceneTree* SceneManager::createSceneTest1() {
    SceneTree* sceneTree = new SceneTree();
    GameObject* player = GameObjectFactory::createPlayerTest();
    sceneTree->addChild(player);
    GameObject* bow = GameObjectFactory::createBow();
    player->getSceneNode()->addChild(bow);
    
    for (int i = 0; i < 10; i++) {
        GameObject* enemy = GameObjectFactory::createEnemyWarrior();
        enemy->getComponent<Transform>()->setPositionInScreen(100 + i * 50, 100);
        sceneTree->addChild(enemy);
    }

    return sceneTree;
}

void SceneManager::input()
{
    auto sceneTree = SceneManager::getInstance().m_sceneTree;
    if (sceneTree == nullptr) return;

    sceneTree->traverseTree([](SceneNode* node) {
        if (node->getGameObject())
            node->getGameObject()->input();
    });
}

void SceneManager::update()
{
    auto sceneTree = SceneManager::getInstance().m_sceneTree;
    if (sceneTree == nullptr) return;

    sceneTree->traverseTree([](SceneNode* node) {
        if (node->getGameObject())
            node->getGameObject()->update();
    });
}

void SceneManager::render()
{
    auto sceneTree = SceneManager::getInstance().m_sceneTree;
    if (sceneTree == nullptr) return;

    sceneTree->traverseTree([](SceneNode* node) {
        if (node->getGameObject())
            node->getGameObject()->render();
    });
}
