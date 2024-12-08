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
    
    auto player = players[0];
    
    auto playerCollide = player->getComponent<Collide>();

    m_collide = collide->isColliding(playerCollide);
}

void CollideTestScript::render() {
    auto collide = m_owner->getComponent<Collide>();

    
    if (m_collide) {
        // std::cout << "Collide with player" << std::endl;
        // draw a red rectangle around the object this script is attached to equal to its hitbox
        SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 255, 0, 0, 255);
        SDL_Rect rect = {collide->getPositionX(), collide->getPositionY(), collide->getSizeW(), collide->getSizeH()};
        SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), &rect);
    }
}