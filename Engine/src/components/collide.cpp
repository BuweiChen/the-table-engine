#include "SDL2/SDL.h"

#include "collide.h"
#include "transform.h"
#include "gameobject.h"

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

int Collide::getPositionX()
{
    return mCollide->x;
}

int Collide::getPositionY()
{
    return mCollide->y;
}

int Collide::getSizeW()
{
    return mCollide->w;
}

int Collide::getSizeH()
{
    return mCollide->h;
}

void Collide::setTransformOffset(int x, int y)
{
    mOffsetX = x;
    mOffsetY = y;
}

void Collide::setPositionInScreen(int x, int y)
{
    mCollide->x = x;
    mCollide->y = y;
}

void Collide::setSizeInScreen(int w, int h)
{
    mCollide->w = w;
    mCollide->h = h;
}

void Collide::updatePositionInScreen(int dx, int dy)
{
    mCollide->x += dx;
    mCollide->y += dy;
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
    setPositionInScreen(transform->getPositionX() + mOffsetX, transform->getPositionY() + mOffsetY);
}
