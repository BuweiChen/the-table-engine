#include <iostream>

#include "arrow_test_script.h"
#include "transform.h"
#include "gameobject.h"
#include "collide.h"
#include "scenemanager.h"

ArrowTestScript::ArrowTestScript(float dx, float dy) {
    float norm = sqrt(dx * dx + dy * dy);
    float speed = 12;
    m_dx = dx / norm * speed;
    m_dy = dy / norm * speed;
}

void ArrowTestScript::update() {
    auto transform = m_owner->getComponent<Transform>();

    // Move the arrow
    Vec2 position = transform->getWorldPosition();
    position.x += m_dx;
    position.y += m_dy;
    transform->setWorldPosition(position);

    // Destroy the arrow if it goes off screen
    // Vec2 screen_position = transform->getScreenPosition();
    // if (screen_position.x < 0 || screen_position.x > 640 || screen_position.y < 0 || screen_position.y > 480) {
    //     m_owner->getSceneNode()->setDestroy(true);
    //     return;
    // }

    // Destroy the arrow if it goes very far into the world
    if (position.x < -1200 || position.x > 1200 || position.y < -1200 || position.y > 1200) {
        m_owner->getSceneNode()->setDestroy(true);
        return;
    }

    // Check collision with enemies
    auto sceneTree = SceneManager::getInstance().getSceneTree();
    auto enemies = sceneTree->findGameObjectsByTag("Warrior");
    auto collide = m_owner->getComponent<Collide>();
    for (auto enemy : enemies) {
        if (collide->isColliding(enemy->getComponent<Collide>()->getRect())) {
            m_owner->getSceneNode()->setDestroy(true);
            enemy->getSceneNode()->setDestroy(true);
            break;
        }
    }
}

