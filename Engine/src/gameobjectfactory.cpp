#include "gameobjectfactory.h"

#include "texture.h"
#include "transform.h"
#include "resourcemanager.h"

GameObject* GameObjectFactory::createPlayerTest() 
{
    GameObject* player = new GameObject("Player");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/test.bmp");
    auto texture = new Texture(sdl_texture);
    player->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setSizeInScreen(40, 40);
    transform->setPositionInScreen(200, 200);
    player->addComponent<Transform>(transform);

    return player;
}

GameObject* GameObjectFactory::createAxe() 
{
    GameObject* axe = new GameObject("Axe");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Weapons/Wood/Wood.bmp");
    auto texture = new Texture(sdl_texture);
    texture->setPositionInSpriteMap(48, 48);
    texture->setSizeInSpriteMap(48, 32);
    texture->setAnimationRowsCols(1, 3);
    texture->setAnimationTime(0.2);
    axe->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setSizeInScreen(40, 40);
    transform->setPositionInScreen(300, 300);
    axe->addComponent<Transform>(transform);

    return axe;
}

GameObject* GameObjectFactory::createEnemyWarriorDying() 
{
    GameObject* enemy = new GameObject("Warrior");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Enemy/OrcCrew/Warrior/Death/Death-Sheet.bmp");
    auto texture = new Texture(sdl_texture);
    texture->setAnimationRowsCols(1, 6);
    texture->setAnimationTime(0.2);
    enemy->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setSizeInScreen(80, 80);
    transform->setPositionInScreen(50, 50);
    enemy->addComponent<Transform>(transform);

    return enemy;
}