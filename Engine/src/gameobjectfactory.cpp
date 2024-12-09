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

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Heroes/Knight/Run/Run-Sheet.bmp");
    auto texture = new Texture(sdl_texture);
    texture->setRowsColsInSpriteMap(1, 6);
    texture->setAnimationTime(0.5);
    player->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setWorldPosition(200, 200);
    transform->setWorldSize(80, 80);
    player->addComponent<Transform>(transform);

    auto input = new Input();
    player->addComponent<Input>(input);

    auto playerMovement = new PlayerTestScript();
    player->addScript<PlayerTestScript>(playerMovement);

    auto playerCollide = new Collide();
    playerCollide->setScreenSize(transform->getScreenSize().x * 0.4, transform->getScreenSize().y * 0.6);
    playerCollide->setTransformOffset(transform->getScreenSize().x * 0.3, transform->getScreenSize().y * 0.45);
    player->addComponent<Collide>(playerCollide);

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
    transform->setWorldPosition(240, 248);
    transform->setWorldSize(25, 25);
    bow->addComponent<Transform>(transform);

    auto bowScript = new Bow_script();
    bow->addScript<Bow_script>(bowScript);

    auto input = new Input();
    bow->addComponent<Input>(input);

    auto bowCollide = new Collide();
    bow->addComponent<Collide>(bowCollide);

    return bow;
}

GameObject* GameObjectFactory::createArrow(int dx, int dy) 
{
    GameObject* arrow = new GameObject("Arrow");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Weapons/Wood/Wood.bmp");
    auto texture = new Texture(sdl_texture);

    if (abs(dx) >= abs(dy)) texture->setPositionInSpriteMap(32, 0); // horizontal arrow
    else texture->setPositionInSpriteMap(16, 0); // vertical arrow
    if (dx < 0) texture->setFlipHorizontal(true);
    if (dy > 0) texture->setFlipVertical(true);

    texture->setSizeInSpriteMap(16, 16);
    arrow->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setWorldPosition(225, 208);
    transform->setWorldSize(15, 15);
    arrow->addComponent<Transform>(transform);

    auto arrowMovement = new ArrowTestScript(dx, dy);
    arrow->addScript<ArrowTestScript>(arrowMovement);

    auto arrowCollide = new Collide();
    arrowCollide->setScreenPosition(transform->getScreenPosition());
    arrowCollide->setScreenSize(transform->getScreenSize());
    arrow->addComponent<Collide>(arrowCollide);

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
    transform->setWorldSize(80, 80);
    transform->setWorldPosition(50, 50);
    enemy->addComponent<Transform>(transform);

    auto enemyAI = new EnemyAIScript();
    enemy->addScript<EnemyAIScript>(enemyAI);

    auto enemyCollide = new Collide();
    enemyCollide->setScreenSize(transform->getScreenSize().x * 0.4, transform->getScreenSize().y * 0.6);
    enemyCollide->setTransformOffset(transform->getScreenSize().x * 0.3, transform->getScreenSize().y * 0.45);
    enemy->addComponent<Collide>(enemyCollide);

    auto collideTest = new CollideTestScript();
    enemy->addScript<CollideTestScript>(collideTest);

    return enemy;
}

GameObject* GameObjectFactory::createTile1()
{
    GameObject* tile = new GameObject("Tile");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Environment/DungeonPrison/Assets/Tiles.bmp");
    auto texture = new Texture(sdl_texture);
    texture->setSizeInSpriteMap(32, 32);
    tile->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setWorldSize(32, 32);
    tile->addComponent<Transform>(transform);

    return tile;
}
