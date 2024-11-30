#include "gameobject.h"
#include "transform.h"
#include "resourcemanager.h"
#include "renderer.h"
#include "scenemanager.h"

#include <iostream>

SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::setRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

void SceneManager::setSceneTree(SceneTree* sceneTree) {
    m_sceneTree = sceneTree;
}

SceneTree* SceneManager::createScene1() {
    SceneTree* sceneTree = new SceneTree();

    GameObject* player = new GameObject("Player");

    auto renderer = new Renderer(m_renderer);
    SDL_Texture* texture = ResourceManager::getInstance().loadTexture("../Assets/test.bmp");
    renderer->setTexture(texture);
    player->addComponent<Renderer>(renderer);

    auto transform = new Transform();
    transform->setSize(40, 40);
    transform->setPosition(200, 200);
    player->addComponent<Transform>(transform);

    sceneTree->getRoot()->addChild(player);
    return sceneTree;
}

void SceneManager::input()
{
    auto sceneTree = SceneManager::getInstance().m_sceneTree;

    sceneTree->traverseTree([](SceneNode* node) {
        if (node->getGameObject())
            node->getGameObject()->input();
    });
}

void SceneManager::update()
{
    auto sceneTree = SceneManager::getInstance().m_sceneTree;

    sceneTree->traverseTree([](SceneNode* node) {
        if (node->getGameObject())
            node->getGameObject()->update();
    });
}

void SceneManager::render()
{
    auto sceneTree = SceneManager::getInstance().m_sceneTree;

    sceneTree->traverseTree([](SceneNode* node) {
        if (node->getGameObject())
            node->getGameObject()->render();
    });
}