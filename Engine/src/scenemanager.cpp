#include "gameobject.h"
#include "transform.h"
#include "resourcemanager.h"
#include "texture.h"
#include "scenemanager.h"

#include <iostream>

SceneManager& SceneManager::getInstance() {
    static SceneManager instance;
    return instance;
}

void SceneManager::setRenderer(SDL_Renderer* renderer) {
    m_renderer = renderer;
}

void SceneManager::getNextScene() {
    ++m_currentSceneIndex;
    switch (m_currentSceneIndex) {
        case 1:
            m_sceneTree = createScene1();
            break;
        default:
            m_sceneTree = nullptr;
            break;
    }
}

SceneTree* SceneManager::createScene1() {
    SceneTree* sceneTree = new SceneTree();

    GameObject* player = new GameObject("Player");

    auto texture = new Texture();
    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/test.bmp");
    texture->setTexture(sdl_texture);
    player->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setSize(40, 40);
    transform->setPosition(200, 200);
    player->addComponent<Transform>(transform);

    sceneTree->addChild(player);
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
