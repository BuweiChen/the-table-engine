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
    transform->setSize(40, 40);
    transform->setPosition(200, 200);
    player->addComponent<Transform>(transform);

    return player;
}

GameObject* GameObjectFactory::createAxe() 
{
    GameObject* axe = new GameObject("Axe");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Weapons/Wood/Wood.bmp");
    auto texture = new Texture(sdl_texture);
    axe->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setSize(200, 100);
    transform->setPosition(300, 300);
    axe->addComponent<Transform>(transform);

    return axe;
}