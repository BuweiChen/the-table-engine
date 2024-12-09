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

    int dx = player->getComponent<Transform>()->getPositionX() - player->getComponent<Transform>()->getSizeW() / 2 - transform->getPositionX();
    int dy = player->getComponent<Transform>()->getPositionY() - player->getComponent<Transform>()->getSizeH() - transform->getPositionY();

    texture->setFlipHorizontal(dx < 0);

    float norm = sqrt(dx * dx + dy * dy);
    dx = dx / norm * m_speed;
    dy = dy / norm * m_speed;

    // add some more randomness to the movement
    int val = rand() % 50;
    dx += (val == 0 ? 1 : val == 1 ? -1 : 0);
    dy += (val == 2 ? 1 : val == 3 ? -1 : 0);

    transform->updatePositionInScreen(dx, dy);
}
