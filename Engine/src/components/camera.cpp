#include <iostream>

#include "camera.h"
#include "health.h"
#include "scenemanager.h"
#include "gameobject.h"
#include "transform.h"

Camera::Camera() {
    m_worldPosition = Vec2(0, 0);
}

Camera::~Camera() {
    return;
}

void Camera::update() {
    static int health = -1;
    // auto sceneTree = SceneManager::getInstance().getSceneTree();
    auto player = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Player")[0];
    if (player == nullptr) return;

    int playerHealth = player->getComponent<Health>()->getHealth();
    bool shakeCamera = false;
    if (playerHealth != health) {
        shakeCamera = true;
        health = playerHealth;
    }

    Vec2 playerPosition = player->getComponent<Transform>()->getWorldPosition();
    m_worldPosition = playerPosition;

    if (shakeCamera) {
        m_worldPosition.x += rand() % 10 - 5;
        m_worldPosition.y += rand() % 10 - 5;
    }

    if (SceneManager::getInstance().isDemo)
    {
    if (m_worldPosition.x < -320)
        m_worldPosition.x = -320;
    if (m_worldPosition.x > 320)
        m_worldPosition.x = 320;
    if (m_worldPosition.y < -400)
        m_worldPosition.y = -400;
    if (m_worldPosition.y > 400)
        m_worldPosition.y = 400;
    }
    else
    {
        if (m_worldPosition.x < 320)
            m_worldPosition.x = 320;
        if (m_worldPosition.x > 480)
            m_worldPosition.x = 480;
        if (m_worldPosition.y < 272)
            m_worldPosition.y = 272;
        if (m_worldPosition.y > 560)
            m_worldPosition.y = 560;
    }
}

Vec2 Camera::getWorldPosition() {
    return m_worldPosition;
}

void Camera::setWorldPosition(float x, float y) {
    m_worldPosition = Vec2(x, y);
}
