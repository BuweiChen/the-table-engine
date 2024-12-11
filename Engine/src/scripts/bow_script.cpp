#include <cmath>
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
    auto transform = m_owner->getComponent<Transform>();
    auto texture = m_owner->getComponent<Texture>();

    int bowX = transform->getScreenPosition().x;
    int bowY = transform->getScreenPosition().y;
    int dx = input->m_mouseX - bowX;
    int dy = input->m_mouseY - bowY;

    float angle = std::atan2((float)dy, (float)dx) * (180.0f / (float)M_PI);
    texture->setAngle(angle);

    texture->setFlipHorizontal(dx < 0);

    if (m_shoot && (int)SDL_GetTicks() - m_lastFireTimeInMs > 1000 / m_fireRatePerSecond) {
        m_lastFireTimeInMs = SDL_GetTicks();

        auto arrow = GameObjectFactory::createArrow(dx, dy);
        arrow->getComponent<Transform>()->setWorldPosition(transform->getWorldPosition());

        auto sceneTree = SceneManager::getInstance().getSceneTree();
        sceneTree->addChild(arrow);

        m_shoot = false;
    }
}
