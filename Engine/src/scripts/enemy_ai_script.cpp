#include "enemy_ai_script.h"
#include "scenemanager.h"
#include "gameobject.h"
#include "transform.h"
#include "texture.h"

// Random speed between 2 and 4 float
EnemyAIScript::EnemyAIScript() {
    float val = (float) rand() / RAND_MAX;
    m_speed = 2 + val * 2;
}

void EnemyAIScript::update() {
    auto transform = m_owner->getComponent<Transform>();
    auto texture = m_owner->getComponent<Texture>();
    
    auto players = SceneManager::getInstance().getSceneTree()->findGameObjectsByTag("Player");
    if (players.empty()) return;
    auto player = players[0];

    float dx = player->getComponent<Transform>()->getWorldPosition().x - transform->getWorldPosition().x;
    float dy = player->getComponent<Transform>()->getWorldPosition().y - transform->getWorldPosition().y;

    texture->setFlipHorizontal(dx < 0);

    float norm = sqrt(dx * dx + dy * dy);
    dx = dx / norm * m_speed;
    dy = dy / norm * m_speed;

    // add some more randomness to the movement
    dx += (float) rand() / RAND_MAX - 0.5;
    dy += (float) rand() / RAND_MAX - 0.5;

    transform->updateWorldPosition(dx, dy);
}
