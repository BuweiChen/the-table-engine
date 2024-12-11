#include <iostream>

#include "projectile_script.h"
#include "transform.h"
#include "health.h"
#include "gameobject.h"
#include "collide.h"
#include "scenemanager.h"

ProjectileScript::ProjectileScript(float dx, float dy) {
    float norm = sqrt(dx * dx + dy * dy);
    float speed = 12;
    m_dx = dx / norm * speed;
    m_dy = dy / norm * speed;
}

void ProjectileScript::update() {
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
    auto walls = sceneTree->findGameObjectsByTag("Wall");
    for (auto wall: walls) {
        if (collide->isColliding(wall->getComponent<Collide>())) {
            m_owner->getSceneNode()->setDestroy(true);
            break;
        }
    }
    for (auto enemy : enemies) {
        if (collide->isColliding(enemy->getComponent<Collide>())) {
            m_owner->getSceneNode()->setDestroy(true);
            enemy->getComponent<Health>()->updateHealth(-100);
            // static int arrowCount = 0;
            // arrowCount++;
            // std::cout << "Arrow hit enemy " << arrowCount << std::endl;
            if (enemy->getComponent<Health>()->getHealth() <= 0)
                enemy->getSceneNode()->setDestroy(true);
                // std::cout << "Enemy is dead" << std::endl;
            break;
        }
    }
}

