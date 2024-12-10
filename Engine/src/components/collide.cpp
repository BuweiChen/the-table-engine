#include "SDL2/SDL.h"

#include <iostream>

#include "collide.h"
#include "transform.h"
#include "gameobject.h"
#include "scenemanager.h"
#include "vec2.h"

Collide::Collide()
{
    setName("collide");
    mCollide = new SDL_Rect();
    mOffsetX = 0;
    mOffsetY = 0;
}

Collide::~Collide()
{
    delete mCollide;
}

SDL_Rect* Collide::getRect()
{
    return mCollide;
}

SDL_Rect* Collide::nextRect(int dx, int dy)
{
    return new SDL_Rect{(int) getScreenPosition().x + dx, (int) getScreenPosition().y + dy, mCollide->w, mCollide->h};
}

void Collide::preventCollision(Collide* anotherCollide, float& dx, float& dy)
{
    SDL_Rect* intersectRect = new SDL_Rect();
    if (!SDL_HasIntersection(mCollide, anotherCollide->getRect()))
    {
        SDL_IntersectRect(mCollide, anotherCollide->getRect(), intersectRect);
    }

    SDL_Rect* newIntersectRect;

    auto nextFrameRect = nextRect(dx, dy);
    auto anotherRect = anotherCollide->getRect();
    if (!SDL_IntersectRect(nextFrameRect, anotherRect, newIntersectRect) || (newIntersectRect->w < intersectRect->w || newIntersectRect->h < intersectRect->h))
    {
        return;
    }

    nextFrameRect = nextRect(dx, 0);
    if (!SDL_IntersectRect(nextFrameRect, anotherRect, newIntersectRect) || (newIntersectRect->w < intersectRect->w || newIntersectRect->h < intersectRect->h))
    {
        dy = 0;
        return;
    }

    nextFrameRect = nextRect(0, dy);
    if (!SDL_IntersectRect(nextFrameRect, anotherRect, newIntersectRect) || (newIntersectRect->w < intersectRect->w || newIntersectRect->h < intersectRect->h))
    {
        dx = 0;
        return;
    }

    dx = 0;
    dy = 0;
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

    // collider's screen position equals transform's screen position + offset
    float x = transform->getScreenPosition().x;
    float y = transform->getScreenPosition().y;
    setScreenPosition(x + mOffsetX, y + mOffsetY);

    // collider's screen size equals transform's screen size unless manually set
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
