
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

    int x = transform->getPositionX();
    int y = transform->getPositionY();
    int w = transform->getSizeW();
    int h = transform->getSizeH();

    if (input->leftPressed) {
        x -= m_playerSpeed;
    }
    if (input->rightPressed) {
        x += m_playerSpeed;
    }
    if (input->upPressed) {
        y -= m_playerSpeed;
    }
    if (input->downPressed) {
        y += m_playerSpeed;
    }

    // clamp positions to screen
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (x > 640 - w) x = 640 - w;
    if (y > 480 - h) y = 480 - h;

    int dx = x - transform->getPositionX();
    int dy = y - transform->getPositionY();

    transform->setPositionInScreen(x, y);

    // move the player's bow with the player
    auto bow = m_owner->getChildren()[0];
    bow->getComponent<Transform>()->updatePositionInScreen(dx, dy);

    // fire bow if mouse left is pressed
    if (input->mouseLeftPressed && ((int) SDL_GetTicks() - m_lastFireTimeInMs) > 1000 / m_fireRatePerSecond) {
        m_lastFireTimeInMs = SDL_GetTicks();

        std::string shootDir = input->m_mouseX < bow->getComponent<Transform>()->getPositionX() ? "left" : "right";
        auto arrow = GameObjectFactory::createArrow(shootDir);
        arrow->getComponent<Transform>()->setPositionInScreen(x + 30, y + 15);
        arrow->getComponent<Texture>()->setFlipHorizontal(shootDir == "left");

        auto bow = m_owner->getChildren()[0];
        bow->getComponent<Texture>()->setFlipHorizontal(shootDir == "left");

        auto sceneTree = SceneManager::getInstance().getSceneTree();
        sceneTree->addChild(arrow);
    }
}
