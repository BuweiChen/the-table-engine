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

SDL_Rect* Collide::nextRect(float dx, float dy)
{   
    return new SDL_Rect{(int) (mCollide->x + dx), (int) (mCollide->y + dy), mCollide->w, mCollide->h};
}

void Collide::preventCollision(Collide* anotherCollide, float& dx, float& dy)
{
    if (dx == 0 && dy == 0) return;

    auto secondRect = anotherCollide->getRect();

    // if the two colliders are already intersecting, apply a backward force to separate them
    SDL_Rect* intersectRect = new SDL_Rect();
    bool intersects = SDL_IntersectRect(mCollide, secondRect, intersectRect);
    if (intersects)
    {
        bool hitFromSide = intersectRect->w < intersectRect->h;
        if (hitFromSide)
        {
            bool sign = intersectRect->x > mCollide->x;
            dx = (sign ? 1 : -1) * -1;
            dy = 0;
            return;
        }
        else
        {
            bool sign = intersectRect->y > mCollide->y;
            dx = 0;
            dy = (sign ? 1 : -1) * -1;
            return;
        }
    }
    
    auto nextFrameRect = nextRect(dx, 0);
    if (SDL_HasIntersection(nextFrameRect, secondRect))
    {
        dx = 0;
    }

    nextFrameRect = nextRect(0, dy);
    if (SDL_HasIntersection(nextFrameRect, secondRect))
    {
        dy = 0;
    }
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
    // if (m_owner->getTag() == "Player")
    // {
    //     SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 255, 0, 255, 255);
    //     SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), mCollide);
    // }

    // if (m_owner->getTag() == "Bow")
    // {
    //     SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 0, 255, 0, 255);
    //     SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), mCollide);
    // }

    // if (m_owner->getTag() == "Arrow")
    // {
    //     SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 0, 255, 255, 255);
    //     SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), mCollide);
    // }

    // if (m_owner->getTag() == "Key")
    // {
    //     SDL_SetRenderDrawColor(SceneManager::getInstance().getRenderer(), 255, 255, 0, 255);
    //     SDL_RenderDrawRect(SceneManager::getInstance().getRenderer(), mCollide);
    // }
}
