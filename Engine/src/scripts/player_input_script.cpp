
#include "player_input_script.h"

#include "input.h"
#include "transform.h"
#include "texture.h"
#include "collide.h"
#include "gameobject.h"
#include "gameobjectfactory.h"
#include "scenemanager.h"

#include  <iostream>
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

    Vec2 position = transform->getWorldPosition();
    Vec2 size = transform->getScreenSize();

    if (input->leftPressed) {
        position.x -= m_playerSpeed;
    }
    if (input->rightPressed) {
        position.x += m_playerSpeed;
    }
    if (input->upPressed) {
        position.y -= m_playerSpeed;
    }
    if (input->downPressed) {
        position.y += m_playerSpeed;
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

    float dx = position.x - transform->getWorldPosition().x;
    float dy = position.y - transform->getWorldPosition().y;

    texture->setFlipHorizontal(dx < 0);

    // // prevent hitting enemies
    // auto enemies = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Warrior");
    // for (auto enemy : enemies) {
    //     auto enemyCollide = enemy->getComponent<Collide>();
    //     collide->preventCollision(enemyCollide, dx, dy);
    // }

    transform->updateWorldPosition(dx, dy);

    // move the player's bow with the player
    auto bow = m_owner->getChildren()[0];
    bow->getComponent<Transform>()->updateWorldPosition(dx, dy);

    // collect keys
    auto keys = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Key");
    for (auto key : keys) {
        auto keyCollide = key->getComponent<Collide>();
        if (collide->isColliding(keyCollide)) {
            key->getSceneNode()->setDestroy(true);
            m_keysCollected++;
        }
    }
}
