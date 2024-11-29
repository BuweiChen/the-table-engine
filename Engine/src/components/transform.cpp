#include "transform.h"
#include "SDL2/SDL.h"

Transform::Transform()
{
    setName("transform");
    mTransform = new SDL_Rect();
}

Transform::Transform(int x, int y)
{
    Transform();
    mTransform->x = x;
    mTransform->y = y;
}

Transform::~Transform()
{
    delete mTransform;
}

SDL_Rect* Transform::getRect()
{
    return mTransform;
}

int Transform::getPositionX()
{
    return mTransform->x;
}

int Transform::getPositionY()
{
    return mTransform->y;
}

int Transform::getSizeW()
{
    return mTransform->w;
}

int Transform::getSizeH()
{
    return mTransform->h;
}

void Transform::setPosition(int x, int y)
{
    mTransform->x = x;
    mTransform->y = y;
}

void Transform::setSize(int w, int h)
{
    mTransform->w = w;
    mTransform->h = h;
}
