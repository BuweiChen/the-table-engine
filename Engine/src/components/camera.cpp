#include <iostream>

#include "camera.h"
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
    auto player = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Player")[0];
    if (player == nullptr) return;

    Vec2 playerPosition = player->getComponent<Transform>()->getWorldPosition();
    m_worldPosition = playerPosition;

    if (m_worldPosition.x < -320)
        m_worldPosition.x = -320;
    if (m_worldPosition.x > 320)
        m_worldPosition.x = 320;
    if (m_worldPosition.y < -400)
        m_worldPosition.y = -400;
    if (m_worldPosition.y > 400)
        m_worldPosition.y = 400;
}

Vec2 Camera::getWorldPosition() {
    return m_worldPosition;
}

void Camera::setWorldPosition(float x, float y) {
    m_worldPosition = Vec2(x, y);
}
