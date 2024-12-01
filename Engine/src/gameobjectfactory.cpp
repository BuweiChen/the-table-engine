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
