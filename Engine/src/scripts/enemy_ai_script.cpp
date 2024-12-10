#include "enemy_ai_script.h"
#include "scenemanager.h"
#include "gameobject.h"
#include "transform.h"
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

    // prevent the enemy from moving through player
    auto playerCollide = player->getComponent<Collide>();
    // collide->preventCollision(playerCollide, dx, dy);

    // prevent the enemy from moving through other enemies
    auto enemies = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Warrior");
    for (auto enemy : enemies) {
        if (enemy == m_owner) continue;
        auto enemyCollide = enemy->getComponent<Collide>();
        // collide->preventCollision(enemyCollide, dx, dy);
    } 

    transform->updateWorldPosition(dx, dy);
}
