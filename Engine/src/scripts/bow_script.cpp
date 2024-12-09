#include <iostream>

#include "bow_script.h"
#include "gameobject.h"
#include "input.h"
#include "gameobjectfactory.h"
#include "transform.h"
#include "texture.h"
#include "scenemanager.h"

Bow_script::Bow_script() {
    m_shoot = false;
    m_lastFireTimeInMs = -10000;
    m_fireRatePerSecond = 2;
}

void Bow_script::input() {
    if (m_owner->getTag() == "Bow") {
        if (m_owner->getComponent<Input>()->spacePressed) {
            m_shoot = true;
        } else {
            m_shoot = false;
        }
    }
}

void Bow_script::update() {
    auto input = m_owner->getComponent<Input>();
    if (m_shoot && (int) SDL_GetTicks() - m_lastFireTimeInMs > 1000 / m_fireRatePerSecond) {
        int dx = input->m_mouseX - m_owner->getComponent<Transform>()->getPositionX();
        int dy = input->m_mouseY - m_owner->getComponent<Transform>()->getPositionY();
        auto arrow = GameObjectFactory::createArrow(dx, dy);
        arrow->getComponent<Transform>()->setPositionInScreen(m_owner->getComponent<Transform>()->getPositionX(), m_owner->getComponent<Transform>()->getPositionY());
        arrow->getComponent<Texture>()->setFlipHorizontal(input->m_mouseX < m_owner->getComponent<Transform>()->getPositionX());

        auto sceneTree = SceneManager::getInstance().getSceneTree();
        sceneTree->addChild(arrow);
        m_lastFireTimeInMs = SDL_GetTicks();
    }
}