#include <iostream>

#include "arrow_test_script.h"
#include "transform.h"
#include "gameobject.h"
#include "collide.h"
#include "scenemanager.h"

ArrowTestScript::ArrowTestScript(int dx, int dy) {
    m_dx = dx / 20;
    m_dy = dy / 20;
}

void ArrowTestScript::update() {
    auto transform = m_owner->getComponent<Transform>();

    int x = transform->getPositionX();
    int y = transform->getPositionY();

    x += m_dx;
    y += m_dy;

    if (x < 0 || x > 640 || y < 0 || y > 480) {
        m_owner->getSceneNode()->setDestroy(true);
        return;
    }

    transform->setPositionInScreen(x, y);
    
    // Check collision with enemies
    auto sceneTree = SceneManager::getInstance().getSceneTree();
    auto enemies = sceneTree->findGameObjectsByTag("Warrior");
    std::cout << "Enemies: " << enemies.size() << std::endl;
    auto collide = m_owner->getComponent<Collide>();
    for (auto enemy : enemies) {
        if (collide->isColliding(enemy->getComponent<Collide>()->getRect())) {
            m_owner->getSceneNode()->setDestroy(true);
            enemy->getSceneNode()->setDestroy(true);
            break;
        }
    }
}

