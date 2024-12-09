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
        }
    }
}

void Bow_script::update() {
    auto input = m_owner->getComponent<Input>();
    if (m_shoot && (int) SDL_GetTicks() - m_lastFireTimeInMs > 1000 / m_fireRatePerSecond) {
        m_lastFireTimeInMs = SDL_GetTicks();

        int dx = input->m_mouseX - m_owner->getComponent<Transform>()->getScreenPosition().x;
        int dy = input->m_mouseY - m_owner->getComponent<Transform>()->getScreenPosition().y;
        
        auto arrow = GameObjectFactory::createArrow(dx, dy);
        arrow->getComponent<Transform>()->setWorldPosition(m_owner->getComponent<Transform>()->getWorldPosition());

        m_owner->getComponent<Texture>()->setFlipHorizontal(dx < 0);

        auto sceneTree = SceneManager::getInstance().getSceneTree();
        sceneTree->addChild(arrow);
        m_shoot = false;
    }
}