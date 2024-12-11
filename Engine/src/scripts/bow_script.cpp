#include <cmath>
#include "bow_script.h"
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
            animation->setFrame(0);  // Reset to first frame
            animation->play();       // Start the animation
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

    float angle = std::atan2((float)dy, (float)dx) * (180.0f / (float)M_PI);
    animation->setAngle(angle);

    animation->setFlipHorizontal(dx < 0);

    // If animation has completed one cycle (reached last frame)
    if (animation->isPlaying() && animation->getCurrentFrame() == 2 && !m_animationPlayed) {
        animation->pause();
        animation->setFrame(0);  // Reset to first frame
        m_animationPlayed = true;
    }

    if (m_shoot) {
        m_lastFireTimeInMs = SDL_GetTicks();

        auto arrow = GameObjectFactory::createArrow(dx, dy);
        arrow->getComponent<Transform>()->setWorldPosition(transform->getWorldPosition());

        auto sceneTree = SceneManager::getInstance().getSceneTree();
        sceneTree->addChild(arrow);

        m_shoot = false;
    }
}