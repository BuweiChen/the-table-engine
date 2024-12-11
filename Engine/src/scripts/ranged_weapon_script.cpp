#include <cmath>
#include "ranged_weapon_script.h"
#include "gameobject.h"
#include "input.h"
#include "gameobjectfactory.h"
#include "transform.h"
#include "animation.h"
#include "scenemanager.h"

Bow_script::Bow_script() {
    m_shoot = false;
    m_lastFireTimeInMs = -10000;
    m_fireRatePerSecond = 2;
    m_animationPlayed = false;
}

void Bow_script::input() {
    if (m_owner->getTag() == "Bow") {
        auto animation = m_owner->getComponent<Animation>();
        
        if (m_owner->getComponent<Input>()->spacePressed && 
            (int)SDL_GetTicks() - m_lastFireTimeInMs > 1000 / m_fireRatePerSecond) {
            m_shoot = true;
            animation->setFrame(0);
            animation->play(); 
            m_animationPlayed = false;
        }
    }
}

void Bow_script::update() {
    auto input = m_owner->getComponent<Input>();
    auto transform = m_owner->getComponent<Transform>();
    auto animation = m_owner->getComponent<Animation>();

    int bowX = transform->getScreenPosition().x;
    int bowY = transform->getScreenPosition().y;
    int dx = input->m_mouseX - bowX;
    int dy = input->m_mouseY - bowY;

    float angle = atan2(dy, dx) * (180.0f / M_PI);

    if (angle < 0) {
        angle += 360.0f;
    }

    animation->setAngle(angle);

    if (m_shoot) {
        m_lastFireTimeInMs = SDL_GetTicks();

        auto arrow = GameObjectFactory::createArrow(dx, dy);
        arrow->getComponent<Transform>()->setWorldPosition(transform->getWorldPosition());

        auto sceneTree = SceneManager::getInstance().getSceneTree();
        sceneTree->addChild(arrow);

        m_shoot = false;
    }

    if (animation->isPlaying() && animation->getCurrentFrame() == (animation->getNumFrames() - 1) && !m_animationPlayed) {
        animation->pause();
        animation->setFrame(0);
        m_animationPlayed = true;
    }
}
