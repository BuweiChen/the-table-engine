#include "transform.h"
#include "gameobject.h"
#include "scenemanager.h"

#include "SDL2/SDL.h"

#include <iostream>

Transform::Transform()
{
    setName("transform");
    mTransform = new SDL_Rect();
    mPosition = Vec2(0, 0);
}

Transform::Transform(int x, int y)
{
    Transform();
    mTransform->x = x;
    mTransform->y = y;
    mPosition = Vec2(x, y);
}

Transform::~Transform()
{
    delete mTransform;
}

SDL_Rect* Transform::getScreenRect()
{
    return mTransform;
}

Vec2 Transform::getWorldPosition()
{
    return mPosition;
}

Vec2 Transform::getScreenPosition()
{
    return Vec2(mTransform->x, mTransform->y);
}

Vec2 Transform::getScreenSize()
{
    return mSize;
}

void Transform::setWorldPosition(float x, float y)
{
    mPosition = Vec2(x, y);
}

void Transform::setWorldPosition(Vec2 pos)
{
    mPosition = pos;
}

void Transform::setWorldSize(float w, float h)
{
    mSize = Vec2(w, h);
}

void Transform::setWorldSize(Vec2 size)
{
    mSize = size;
}

void Transform::updateWorldPosition(float dx, float dy)
{
    mPosition.x += dx;
    mPosition.y += dy;
}

void Transform::updateWorldPosition(Vec2 dpos)
{
    mPosition.x += dpos.x;
    mPosition.y += dpos.y;
}
 
void Transform::update()
{
    Vec2 cameraPosition = SceneManager::getInstance().getCameraWorldPosition();

    /* calculate screen position relative to the player (camera follows player) */
    mTransform->x = mPosition.x - cameraPosition.x + 320;
    mTransform->y = mPosition.y - cameraPosition.y + 240;
    mTransform->w = mSize.x;
    mTransform->h = mSize.y;
}
