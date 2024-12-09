
#include "player_test_script.h"

#include "input.h"
#include "transform.h"
#include "texture.h"
#include "gameobject.h"
#include "gameobjectfactory.h"
#include "scenemanager.h"

#include  <iostream>
#include <string>

PlayerTestScript::PlayerTestScript() {
    m_lastFireTimeInMs = -10000;
}

void PlayerTestScript::update() {
    auto input = m_owner->getComponent<Input>();
    auto transform = m_owner->getComponent<Transform>();
    auto texture = m_owner->getComponent<Texture>();

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

    // clamp positions to screen
    // if (x < 0) x = 0;
    // if (y < 0) y = 0;
    // if (x > 640 - w) x = 640 - w;
    // if (y > 480 - h) y = 480 - h;

    float dx = position.x - transform->getWorldPosition().x;
    float dy = position.y - transform->getWorldPosition().y;

    texture->setFlipHorizontal(dx < 0);
    transform->setWorldPosition(position);

    // move the player's bow with the player
    auto bow = m_owner->getChildren()[0];
    bow->getComponent<Transform>()->updateWorldPosition(dx, dy);
}
