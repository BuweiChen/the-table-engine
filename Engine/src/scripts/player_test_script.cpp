
#include "player_test_script.h"

#include "input.h"
#include "transform.h"
#include "gameobject.h"

#include  <iostream>

PlayerTestScript::PlayerTestScript(std::string name) : Script(name) {}
PlayerTestScript::~PlayerTestScript() {}

void PlayerTestScript::update() {
    auto input = m_owner->getComponent<Input>();
    auto transform = m_owner->getComponent<Transform>();

    int x = transform->getPositionX();
    int y = transform->getPositionY();
    int w = transform->getSizeW();
    int h = transform->getSizeH();

    if (input->leftPressed) {
        x -= 1;
    }
    if (input->rightPressed) {
        x += 1;
    }
    if (input->upPressed) {
        y -= 1;
    }
    if (input->downPressed) {
        y += 1;
    }

    if (input->mouseLeftPressed) {
        x = input->m_mouseX - w / 2;
        y = input->m_mouseY - h / 2;
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
    for (auto child : m_owner->getChildren()) {
        auto childTransform = child->getComponent<Transform>();
        if (childTransform == nullptr) { continue; }
        childTransform->updatePositionInScreen(dx, dy);
    };
}
