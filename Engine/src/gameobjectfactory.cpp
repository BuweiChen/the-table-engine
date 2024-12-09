#include "gameobjectfactory.h"

#include "texture.h"
#include "transform.h"
#include "collide.h"
#include "input.h"
#include "resourcemanager.h"
#include "player_test_script.h"
#include "arrow_test_script.h"
#include "enemy_ai_script.h"
#include "collide_test_script.h"
#include "collide_script.h"
#include "bow_script.h"

GameObject* GameObjectFactory::createPlayerTest() 
{
    GameObject* player = new GameObject("Player");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/test.bmp");
    auto texture = new Texture(sdl_texture);
    player->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setPositionInScreen(200, 200);
    transform->setSizeInScreen(40, 40);
    player->addComponent<Transform>(transform);

    auto input = new Input();
    player->addComponent<Input>(input);

    auto playerMovement = new PlayerTestScript();
    player->addScript<PlayerTestScript>(playerMovement);

    auto playerCollide = new Collide();
    playerCollide->setPositionInScreen(transform->getPositionX(), transform->getPositionY());
    playerCollide->setSizeInScreen(transform->getSizeW(), transform->getSizeH());
    player->addComponent<Collide>(playerCollide);

    auto collideScript = new CollideScript();
    player->addScript<CollideScript>(collideScript);

    return player;
}

GameObject* GameObjectFactory::createBow() 
{
    GameObject* bow = new GameObject("Bow");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Weapons/Wood/Wood.bmp");
    auto texture = new Texture(sdl_texture);
    texture->setPositionInSpriteMap(48, 48);
    texture->setSizeInSpriteMap(48, 32);
    texture->setRowsColsInSpriteMap(1, 3);
    texture->setAnimationTime(0.4);
    bow->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setPositionInScreen(225, 208);
    transform->setSizeInScreen(30, 30);
    bow->addComponent<Transform>(transform);

    auto bowScript = new Bow_script();
    bow->addScript<Bow_script>(bowScript);

    auto input = new Input();
    bow->addComponent<Input>(input);

    return bow;
}

GameObject* GameObjectFactory::createArrow(int dx, int dy) 
{
    GameObject* arrow = new GameObject("arrow");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Weapons/Wood/Wood.bmp");
    auto texture = new Texture(sdl_texture);
    texture->setPositionInSpriteMap(32, 0);
    texture->setSizeInSpriteMap(16, 16);
    arrow->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setPositionInScreen(225, 208);
    transform->setSizeInScreen(15, 15);
    arrow->addComponent<Transform>(transform);

    auto arrowMovement = new ArrowTestScript(dx, dy);
    arrow->addScript<ArrowTestScript>(arrowMovement);

    auto arrowCollide = new Collide();
    arrowCollide->setPositionInScreen(transform->getPositionX(), transform->getPositionY());
    arrowCollide->setSizeInScreen(transform->getSizeW(), transform->getSizeH());
    arrow->addComponent<Collide>(arrowCollide);

    auto collideScript = new CollideScript();
    arrow->addScript<CollideScript>(collideScript);

    return arrow;
}

GameObject* GameObjectFactory::createEnemyWarrior() 
{
    GameObject* enemy = new GameObject("Warrior");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Enemy/OrcCrew/Warrior/Run/Run-Sheet.bmp");
    auto texture = new Texture(sdl_texture);
    texture->setRowsColsInSpriteMap(1, 6);
    texture->setAnimationTime(0.5);
    enemy->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setSizeInScreen(80, 80);
    transform->setPositionInScreen(50, 50);
    enemy->addComponent<Transform>(transform);

    auto enemyAI = new EnemyAIScript();
    enemy->addScript<EnemyAIScript>(enemyAI);

    auto enemyCollide = new Collide();
    enemyCollide->setPositionInScreen(transform->getPositionX(), transform->getPositionY());
    enemyCollide->setSizeInScreen(transform->getSizeW(), transform->getSizeH());
    enemy->addComponent<Collide>(enemyCollide);

    auto collideTest = new CollideTestScript();
    enemy->addScript<CollideTestScript>(collideTest);

    auto collideScript = new CollideScript();
    enemy->addScript<CollideScript>(collideScript);

    return enemy;
}
