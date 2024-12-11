#include <iostream>

#include "enemy_ai_script.h"
#include "scenemanager.h"
#include "gameobject.h"
#include "transform.h"
#include "health.h"
#include "collide.h"
#include "texture.h"

// Random speed between 2 and 4 float
EnemyAIScript::EnemyAIScript() {
    float val = (float) rand() / RAND_MAX;
    m_speed = 2 + val * 2;
}

void EnemyAIScript::update() {
    auto transform = m_owner->getComponent<Transform>();
    auto texture = m_owner->getComponent<Texture>();
    auto collide = m_owner->getComponent<Collide>();
    
    // move the enemy towards the player
    auto players = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Player");
    if (players.empty()) return;
    auto player = players[0];

    float dx = player->getComponent<Transform>()->getWorldPosition().x - transform->getWorldPosition().x;
    float dy = player->getComponent<Transform>()->getWorldPosition().y - transform->getWorldPosition().y;

    float norm = sqrt(dx * dx + dy * dy);
    dx = dx / norm * m_speed;
    dy = dy / norm * m_speed;

    // enemy faces the player
    texture->setFlipHorizontal(dx < 0);

    // prevent the enemy from moving through other enemies
    auto enemies = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Warrior");
    for (auto enemy : enemies) {
        if (enemy == m_owner) continue;
        auto enemyCollide = enemy->getComponent<Collide>();
        collide->preventCollision(enemyCollide, dx, dy);
    } 

    // prevent hitting walls
    auto walls = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Wall");
    for (auto wall : walls) {
        auto wallCollide = wall->getComponent<Collide>();
        collide->preventCollision(wallCollide, dx, dy);
    }

    // prevent hitting tables
    auto tables = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Table");
    for (auto table : tables) {
        auto tableCollide = table->getComponent<Collide>();
        collide->preventCollision(tableCollide, dx, dy);
    }

    // prevent the enemy from moving through player
    // auto playerCollide = player->getComponent<Collide>();
    // collide->preventCollision(playerCollide, dx, dy);

    transform->updateWorldPosition(dx, dy);
}

void EnemyAIScript::render() {
    // place a health bar above the enemy
    auto transform = m_owner->getComponent<Transform>();
    Vec2 screenPos = transform->getScreenPosition();
    Vec2 screenSize = transform->getScreenSize();
    
    auto health = m_owner->getComponent<Health>();
    int health_width = (int) (20.0 * health->getHealth() / 200);
    SDL_Rect rect = {(int) (screenPos.x + screenSize.x / 2) - 10, (int) (screenPos.y + screenSize.y / 2) - 8, health_width, 6};
    SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 255, 0, 0, 255);
    SDL_RenderFillRect(SceneManager::getInstance().getRenderer(), &rect);
    // draw a border around the health bar
    rect = {(int) (screenPos.x + screenSize.x / 2) - 10, (int) (screenPos.y + screenSize.y / 2) - 8, 20, 6};
    SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 0, 0, 0, 255);
    SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), &rect);
}
