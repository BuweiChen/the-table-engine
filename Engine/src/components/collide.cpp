#include "SDL2/SDL.h"

#include <iostream>

#include "collide.h"
#include "transform.h"
#include "gameobject.h"
#include "scenemanager.h"

Collide::Collide()
{
    setName("collide");
    mCollide = new SDL_Rect();
    mOffsetX = 0;
    mOffsetY = 0;
}

Collide::Collide(int x, int y, int w, int h)
{
    Collide();
    mCollide->x = x;
    mCollide->y = y;
    mCollide->w = w;
    mCollide->h = h;
}

Collide::Collide(SDL_Rect* rect)
{
    Collide();
    mCollide->x = rect->x;
    mCollide->y = rect->y;
    mCollide->w = rect->w;
    mCollide->h = rect->h;
}

Collide::~Collide()
{
    delete mCollide;
}

SDL_Rect* Collide::getRect()
{
    return mCollide;
}

Vec2 Collide::getScreenPosition()
{
    return Vec2(mCollide->x, mCollide->y);
}

Vec2 Collide::getScreenSize()
{
    return Vec2(mCollide->w, mCollide->h);
}

void Collide::setTransformOffset(int x, int y)
{
    mOffsetX = x;
    mOffsetY = y;
}

void Collide::setScreenPosition(int x, int y)
{
    mCollide->x = x;
    mCollide->y = y;
}

void Collide::setScreenSize(int w, int h)
{
    mCollide->w = w;
    mCollide->h = h;
}

void Collide::setScreenPosition(Vec2 pos)
{
    mCollide->x = pos.x;
    mCollide->y = pos.y;
}

void Collide::setScreenSize(Vec2 size)
{
    mCollide->w = size.x;
    mCollide->h = size.y;
}

bool Collide::isColliding(SDL_Rect* rect)
{
    return SDL_HasIntersection(mCollide, rect);
}

bool Collide::isColliding(Collide* collide)
{
    return SDL_HasIntersection(mCollide, collide->getRect());
}

void Collide::update()
{
    auto transform = m_owner->getComponent<Transform>();
    if (transform == NULL) return;

    auto sceneTree = SceneManager::getInstance().getSceneTree();
    auto player = sceneTree->findGameObjectsByTag("Player")[0];
    auto playerTransform = player->getComponent<Transform>();

    float x = transform->getWorldPosition().x - playerTransform->getWorldPosition().x + 320;
    float y = transform->getWorldPosition().y - playerTransform->getWorldPosition().y + 240;
    setScreenPosition(x + mOffsetX, y + mOffsetY);

    if (getScreenSize() == Vec2(0, 0))
    {
        setScreenSize(transform->getScreenSize());
    }
}

// solely for debugging/visual purposes
void Collide::render()
{
    if (m_owner->getTag() == "Player")
    {
        SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 255, 0, 255, 255);
        SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), mCollide);
    }

    if (m_owner->getTag() == "Bow")
    {
        SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 0, 255, 0, 255);
        SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), mCollide);
    }

    if (m_owner->getTag() == "Arrow")
    {
        SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 0, 255, 255, 255);
        SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), mCollide);
    }

    if (m_owner->getTag() == "Key")
    {
        SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 255, 255, 0, 255);
        SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), mCollide);
    }
}
