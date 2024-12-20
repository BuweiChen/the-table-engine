#include <iostream>

#include "gameobjectfactory.h"

#include "texture.h"
#include "transform.h"
#include "animation.h"
#include "animationsmanager.h"
#include "collide.h"
#include "input.h"
#include "health.h"
#include "resourcemanager.h"
#include "player_input_script.h"
#include "projectile_script.h"
#include "enemy_ai_script.h"
#include "collision_script.h"
#include "ranged_weapon_script.h"
#include "crosshair_script.h"

GameObject* GameObjectFactory::createPlayerTest() 
{
    GameObject* player = new GameObject("Player");

    // Create animation manager and load all animations
    auto animations = new AnimationsManager();

    // Idle animation
    SDL_Texture* idleTexture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Heroes/Knight/Idle/Idle-Sheet.bmp");
    int idleAnim = animations->createAnimation(idleTexture, 1, 4, 0.5f);
    
    // Run animation
    SDL_Texture* runTexture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Heroes/Knight/Run/Run-Sheet.bmp");
    animations->createAnimation(runTexture, 1, 6, 0.5f);
    
    // Death animation
    SDL_Texture* deathTexture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Heroes/Knight/Death/Death-Sheet.bmp");
    animations->createAnimation(deathTexture, 1, 6, 0.5f);

    // Set initial animation
    animations->setCurrentAnimation(idleAnim);
    player->addComponent<Texture>(animations);

    // Rest of the player setup remains the same
    auto transform = new Transform();
    transform->setWorldPosition(200, 200);
    transform->setWorldSize(40, 40);
    player->addComponent<Transform>(transform);

    auto input = new Input();
    player->addComponent<Input>(input);

    auto health = new Health(1000);
    player->addComponent<Health>(health);

    auto playerMovement = new PlayerInputScript();
    player->addScript<PlayerInputScript>(playerMovement);

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
    auto animation = new Animation(sdl_texture);
    animation->setPositionInSpriteMap(48, 48);
    animation->setSizeInSpriteMap(48, 32);
    animation->setRowsColsInSpriteMap(1, 3);
    animation->setAnimationTime(0.4);
    animation->setAutoPlay(false); 
    animation->setFrame(0);
    bow->addComponent<Animation>(animation);

    auto transform = new Transform();
    transform->setWorldPosition(240, 248);
    transform->setWorldSize(25, 25);
    bow->addComponent<Transform>(transform);

    auto bowScript = new RangedWeaponScript();
    bow->addScript<RangedWeaponScript>(bowScript);

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

    auto arrowMovement = new ProjectileScript(dx, dy);
    arrow->addScript<ProjectileScript>(arrowMovement);

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
    auto texture = new Animation(sdl_texture);
    texture->setRowsColsInSpriteMap(1, 6);
    texture->setAnimationTime(0.5);
    enemy->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setWorldSize(40, 40);
    transform->setWorldPosition(50, 50);
    enemy->addComponent<Transform>(transform);

    auto health = new Health(200);
    enemy->addComponent<Health>(health);

    auto enemyAI = new EnemyAIScript();
    enemy->addScript<EnemyAIScript>(enemyAI);

    auto enemyCollide = new Collide();
    enemyCollide->setScreenSize(transform->getScreenSize().x * 0.4, transform->getScreenSize().y * 0.6);
    enemyCollide->setTransformOffset(transform->getScreenSize().x * 0.3, transform->getScreenSize().y * 0.45);
    enemy->addComponent<Collide>(enemyCollide);

    auto collideTest = new CollisionScript();
    enemy->addScript<CollisionScript>(collideTest);

    return enemy;
}

GameObject* GameObjectFactory::createEnemyWarriorCustom(std::string path, int row, int col, float animationTime, int pos_x, int pos_y, int size_x, int size_y)
{
    GameObject* enemy = new GameObject("Warrior");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture(path);
    auto texture = new Animation(sdl_texture);
    texture->setRowsColsInSpriteMap(row, col);
    texture->setAnimationTime(animationTime);
    std::cout << animationTime << "\n";
    enemy->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setWorldSize(size_x, size_y);
    transform->setWorldPosition(pos_x, pos_y);
    enemy->addComponent<Transform>(transform);

    auto health = new Health(200);
    enemy->addComponent<Health>(health);

    auto enemyAI = new EnemyAIScript();
    enemy->addScript<EnemyAIScript>(enemyAI);

    auto enemyCollide = new Collide();
    enemyCollide->setScreenSize(transform->getScreenSize().x * 0.4, transform->getScreenSize().y * 0.6);
    enemyCollide->setTransformOffset(transform->getScreenSize().x * 0.3, transform->getScreenSize().y * 0.45);
    enemy->addComponent<Collide>(enemyCollide);

    auto collideTest = new CollisionScript();
    enemy->addScript<CollisionScript>(collideTest);

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

GameObject* GameObjectFactory::createTileCustom(std::string path, Vec2 pos, Vec2 size, Vec2 sprite_size, Vec2 sprite_pos, Vec2 rc)
{
    GameObject* tile = new GameObject("Tile");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture(path);
    auto texture = new Animation(sdl_texture);
    texture->setRowsColsInSpriteMap(rc.x, rc.y);
    texture->setSizeInSpriteMap(sprite_size.x, sprite_size.y);
    texture->setPositionInSpriteMap(sprite_pos.x, sprite_pos.y);
    tile->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setWorldSize(size.x, size.y);
    transform->setWorldPosition(pos.x, pos.y);
    tile->addComponent<Transform>(transform);

    return tile;
}

GameObject* GameObjectFactory::createWallCustom(std::string path, Vec2 pos, Vec2 size, Vec2 sprite_size, Vec2 sprite_pos)
{
    GameObject* wall = new GameObject("Wall");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture(path);
    auto texture = new Texture(sdl_texture);
    // texture->setRowsColsInSpriteMap(rowcols.x, rowcols.y);
    texture->setSizeInSpriteMap(sprite_size.x, sprite_size.y);
    texture->setPositionInSpriteMap(sprite_pos.x, sprite_pos.y);
    wall->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setWorldSize(size.x, size.y);
    transform->setWorldPosition(pos.x, pos.y);
    wall->addComponent<Transform>(transform);

    auto wallCollide = new Collide();
    wallCollide->setScreenSize(transform->getScreenSize());
    wall->addComponent<Collide>(wallCollide);

    return wall;
}

GameObject* GameObjectFactory::createTableCustom(std::string path, Vec2 pos, Vec2 size, Vec2 sprite_size, Vec2 sprite_pos)
{
    // same as a wall expect projectiles can fly over it
    GameObject* table = new GameObject("Table");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture(path);
    auto texture = new Texture(sdl_texture);
    texture->setSizeInSpriteMap(sprite_size.x, sprite_size.y);
    texture->setPositionInSpriteMap(sprite_pos.x, sprite_pos.y);
    table->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setWorldSize(size.x, size.y);
    transform->setWorldPosition(pos.x, pos.y);
    table->addComponent<Transform>(transform);

    auto tableCollide = new Collide();
    tableCollide->setScreenSize(transform->getScreenSize());
    table->addComponent<Collide>(tableCollide);

    return table;

}

GameObject* GameObjectFactory::createKey()
{
    GameObject* key = new GameObject("Key");

    SDL_Texture* sdl_texture = ResourceManager::getInstance().loadTexture("../Assets/PixelCrawler/Environment/DungeonPrison/Assets/Props.bmp");
    auto texture = new Texture(sdl_texture);
    texture->setPositionInSpriteMap(32, 64);
    texture->setSizeInSpriteMap(16, 16);
    key->addComponent<Texture>(texture);

    auto transform = new Transform();
    transform->setWorldSize(32, 32);
    key->addComponent<Transform>(transform);

    auto keyCollide = new Collide();
    keyCollide->setScreenSize(transform->getScreenSize());
    key->addComponent<Collide>(keyCollide);

    return key;
}

GameObject* GameObjectFactory::createCrosshair() {
    GameObject* crosshair = new GameObject("Crosshair");

    SDL_Texture* texture = ResourceManager::getInstance().loadTexture("../Assets/Misc/crosshair.bmp");
    auto textureComponent = new Texture(texture);
    crosshair->addComponent<Texture>(textureComponent);

    auto transform = new Transform();
    transform->setWorldSize(16, 16); 
    crosshair->addComponent<Transform>(transform);

    auto input = new Input();
    crosshair->addComponent<Input>(input);

    auto script = new CrosshairScript();
    crosshair->addScript<CrosshairScript>(script);

    return crosshair;
}


