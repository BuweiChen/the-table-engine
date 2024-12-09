#pragma once

#include "component.h"
#include "vec2.h"
#include "gameobject.h"

#include "SDL2/SDL.h"

class Transform : public Component {
    private:
        SDL_Rect* mTransform; // position and size relative to the screen
        Vec2 mPosition; // position in world space
        Vec2 mSize; // size in world space

  public:
        Transform();
        Transform(int x, int y);
        ~Transform();

        SDL_Rect* getScreenRect();

        Vec2 getWorldPosition();
        Vec2 getScreenPosition();
        Vec2 getScreenSize();

        void setWorldPosition(float x, float y);
        void setWorldPosition(Vec2 pos);

        void updateWorldPosition(float dx, float dy);
        void updateWorldPosition(Vec2 dpos);

        void setWorldSize(float w, float h);
        void setWorldSize(Vec2 size);

        void render();
};