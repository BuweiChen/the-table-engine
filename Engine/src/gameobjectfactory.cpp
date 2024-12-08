#include "gameobjectfactory.h"

#include "texture.h"
#include "transform.h"
#include "input.h"
#include "resourcemanager.h"
#include "player_test_script.h"

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

    auto playerMovement = new PlayerTestScript("player_test_script");
    player->addScript<PlayerTestScript>(playerMovement);

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

    return bow;
}

GameObject* GameObjectFactory::createEnemyWarriorDying() 
{
    GameObject* enemy = new GameObject("Warrior");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Enemy/OrcCrew/Warrior/Death/Death-Sheet.bmp");
    auto texture = new Texture(sdl_texture);
    texture->setRowsColsInSpriteMap(1, 6);
    texture->setAnimationTime(0.4);
    enemy->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setSizeInScreen(80, 80);
    transform->setPositionInScreen(50, 50);
    enemy->addComponent<Transform>(transform);

    return enemy;
}