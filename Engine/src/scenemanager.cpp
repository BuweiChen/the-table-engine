#include "gameobject.h"
#include "transform.h"
#include "resourcemanager.h"
#include "texture.h"
#include "scenemanager.h"
#include "gameobjectfactory.h"

std::atomic<uint64_t> SceneManager::m_totalObjects = 0;
std::atomic<uint64_t> SceneManager::m_aliveObjects = 0;

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
        case 2:
            m_sceneTree = createSceneTest2();
            break;
        case 3:
            m_sceneTree = createSceneTest3();
            break;
        default:
            exit(0);
            break;
    }
}

SDL_Renderer* SceneManager::getRenderer() {
    return m_renderer;
}

SceneTree* SceneManager::createSceneTest1() {
    SceneTree* sceneTree = new SceneTree();

    int lenTiles = 20;
    for (int i = -lenTiles; i < lenTiles; i++) {
        for (int j = -lenTiles; j < lenTiles; j++) {
            GameObject* tile = GameObjectFactory::createTile1();
            tile->getComponent<Transform>()->setWorldPosition(i * 32, j * 32);
            sceneTree->addChild(tile, true);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        int x = rand() % 1200 - 600;
        int y = rand() % 1200 - 600;
        GameObject* key = GameObjectFactory::createKey();
        key->getComponent<Transform>()->setWorldPosition(x, y);
        sceneTree->addChild(key);
    }

    GameObject* player = GameObjectFactory::createPlayerTest();
    sceneTree->addChild(player);
    GameObject* bow = GameObjectFactory::createBow();
    player->getSceneNode()->addChild(bow);

    for (int i = 0; i < 10; i++) {
        GameObject* enemy = GameObjectFactory::createEnemyWarrior();
        enemy->getComponent<Transform>()->setWorldPosition(100 + i * 50, 100);
        sceneTree->addChild(enemy);
    }

    return sceneTree;
}


SceneTree* SceneManager::createSceneTest2() {
    SceneTree* sceneTree = new SceneTree();

    int lenTiles = 20;
    for (int i = -lenTiles; i < lenTiles; i++) {
        for (int j = -lenTiles; j < lenTiles; j++) {
            GameObject* tile = GameObjectFactory::createTile1();
            tile->getComponent<Transform>()->setWorldPosition(i * 32, j * 32);
            sceneTree->addChild(tile, true);
        }
    }

    for (int i = 0; i < 20; i++)
    {
        int x = rand() % 1200 - 600;
        int y = rand() % 1200 - 600;
        GameObject* key = GameObjectFactory::createKey();
        key->getComponent<Transform>()->setWorldPosition(x, y);
        sceneTree->addChild(key);
    }

    GameObject* player = GameObjectFactory::createPlayerTest();
    sceneTree->addChild(player);
    GameObject* bow = GameObjectFactory::createBow();
    player->getSceneNode()->addChild(bow);

    for (int i = 0; i < 20; i++) {
        GameObject* enemy = GameObjectFactory::createEnemyWarrior();
        enemy->getComponent<Transform>()->setWorldPosition(100 + i * 50, 100);
        sceneTree->addChild(enemy);
    }

    return sceneTree;
}

SceneTree* SceneManager::createSceneTest3() {
    SceneTree* sceneTree = new SceneTree();

    int lenTiles = 20;
    for (int i = -lenTiles; i < lenTiles; i++) {
        for (int j = -lenTiles; j < lenTiles; j++) {
            GameObject* tile = GameObjectFactory::createTile1();
            tile->getComponent<Transform>()->setWorldPosition(i * 32, j * 32);
            sceneTree->addChild(tile, true);
        }
    }

    for (int i = 0; i < 30; i++)
    {
        int x = rand() % 1200 - 600;
        int y = rand() % 1200 - 600;
        GameObject* key = GameObjectFactory::createKey();
        key->getComponent<Transform>()->setWorldPosition(x, y);
        sceneTree->addChild(key);
    }

    GameObject* player = GameObjectFactory::createPlayerTest();
    sceneTree->addChild(player);
    GameObject* bow = GameObjectFactory::createBow();
    player->getSceneNode()->addChild(bow);

    for (int i = 0; i < 30; i++) {
        GameObject* enemy = GameObjectFactory::createEnemyWarrior();
        enemy->getComponent<Transform>()->setWorldPosition(100 + i * 50, 100);
        sceneTree->addChild(enemy);
    }

    return sceneTree;
}



void SceneManager::cleanTree()
{
    auto sceneTree = SceneManager::getInstance().m_sceneTree;
    if (sceneTree == nullptr) return;

    sceneTree->traverseTree([](SceneNode* node) {
        if (!node->isBackground() && node->readyToDestroy())
            delete node;
    });
}


void SceneManager::input()
{
    auto sceneTree = SceneManager::getInstance().m_sceneTree;
    if (sceneTree == nullptr) return;

    sceneTree->traverseTree([](SceneNode* node) {
        if (!node->isBackground() && node->getGameObject())
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
    
    cleanTree();

    if (sceneTree->gameStatus() == -1)
        exit(0);
    else if (sceneTree->gameStatus() == 1)
        getNextScene();
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
