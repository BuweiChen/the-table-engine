#include <iostream>

#include "collide_test_script.h"
#include "scenemanager.h"
#include "gameobject.h"
#include "collide.h"
#include "texture.h"

CollideTestScript::CollideTestScript() {
    m_collide = false;
}

void CollideTestScript::update() {
    auto collide = m_owner->getComponent<Collide>();
    
    auto players = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Player");
    if (players.empty()) return;
    auto playerCollide = players[0]->getComponent<Collide>();

    m_collide = collide->isColliding(playerCollide);

    auto arrows = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Arrow");
    for (auto arrow : arrows) {
        auto arrowCollide = arrow->getComponent<Collide>();
        if (arrowCollide == nullptr) continue;
        if (collide->isColliding(arrowCollide)) {
            m_owner->getSceneNode()->setDestroy(true);
            arrow->getSceneNode()->setDestroy(true);
        }
    }
}

void CollideTestScript::render() {
    auto collide = m_owner->getComponent<Collide>();
    if (collide == nullptr) return;

    if (m_collide) {
        // draw a red rectangle around the object this script is attached to equal to its hitbox
        SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 255, 0, 0, 255);
        SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), collide->getRect());
    }
}
