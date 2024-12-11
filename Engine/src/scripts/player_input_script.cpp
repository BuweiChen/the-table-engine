// player_input_script.cpp
#include "player_input_script.h"

#include "input.h"
#include "transform.h"
#include "texture.h"
#include "collide.h"
#include "health.h"
#include "gameobject.h"
#include "gameobjectfactory.h"
#include "scenemanager.h"
#include "health.h"
#include "animationsmanager.h"

#include <iostream>
#include <string>

PlayerInputScript::PlayerInputScript() {
    m_lastFireTimeInMs = -10000;
}

int PlayerInputScript::getKeysCollected() {
    return m_keysCollected;
}

void PlayerInputScript::update() {
    auto input = m_owner->getComponent<Input>();
    auto transform = m_owner->getComponent<Transform>();
    auto texture = m_owner->getComponent<Texture>();
    auto collide = m_owner->getComponent<Collide>();
    auto health = m_owner->getComponent<Health>();
    auto animations = dynamic_cast<AnimationsManager*>(texture);

    Vec2 position = transform->getWorldPosition();

    // Handle movement
    float dx = 0, dy = 0;
    bool isMoving = false;

    if (input->leftPressed) {
        dx -= m_playerSpeed;
        isMoving = true;
    }
    if (input->rightPressed) {
        dx += m_playerSpeed;
        isMoving = true;
    }
    if (input->upPressed) {
        dy -= m_playerSpeed;
        isMoving = true;
    }
    if (input->downPressed) {
        dy += m_playerSpeed;
        isMoving = true;
    }

    position.x += dx;
    position.y += dy;

    // Update animation state based on movement and health
    AnimationState newState = m_currentState;
    if (health->getHealth() <= 0) {
        newState = DEATH;
    }
    else if (isMoving) {
        newState = RUN;
    }
    else {
        newState = IDLE;
    }

    // Change animation if state changed
    if (newState != m_currentState && animations) {
        m_currentState = newState;
        animations->setCurrentAnimation(static_cast<size_t>(m_currentState));
    }

    // clamp positions to level
    int levelWidth = 640;
    int levelHeight = 640;
    if (position.x < -levelWidth - 20)
        position.x = -levelWidth - 20;
    if (position.x > levelWidth - 60)
        position.x = levelWidth - 60;
    if (position.y < -levelHeight - 30)
        position.y = -levelHeight - 30;
    if (position.y > levelHeight - 90)
        position.y = levelHeight - 90;

    texture->setFlipHorizontal(dx < 0);

    // decrement health after collision with enemy
    auto enemies = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Warrior");
    for (auto enemy : enemies) {
         auto enemyCollide = enemy->getComponent<Collide>();
         if (collide->isColliding(enemyCollide)) {
            health->updateHealth(-100);
         }
    }

    // prevent hitting walls
    auto walls = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Wall");
    for (auto wall : walls) {
        auto wallCollide = wall->getComponent<Collide>();
        collide->preventCollision(wallCollide, dx, dy);
    }

    // prevent hitting tables

    auto tables = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Table");
    for (auto table : tables) {
        auto tableCollide = table->getComponent<Collide>();
        collide->preventCollision(tableCollide, dx, dy);
    }

    transform->updateWorldPosition(dx, dy);

    // move the player's bow with the player
    if (!m_owner->getChildren().empty()) {
        auto bow = m_owner->getChildren()[0];
        Vec2 bowOffset(16, 8);  // Adjust these values to position the bow correctly
        bow->getComponent<Transform>()->setWorldPosition(position.x + bowOffset.x, position.y + bowOffset.y);
    }

    // collect keys
    auto keys = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Key");
    for (auto key : keys) {
        auto keyCollide = key->getComponent<Collide>();
        if (collide->isColliding(keyCollide)) {
            key->getSceneNode()->setDestroy(true);
            m_keysCollected++;
        }
    }

    // health
    for (auto enemy : SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Warrior")) {
        auto enemyCollide = enemy->getComponent<Collide>();
        if (collide->isColliding(enemyCollide)) {
            health->updateHealth(-10);
        }
    }
}