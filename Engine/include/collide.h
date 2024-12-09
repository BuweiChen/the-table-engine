#pragma once

#include "component.h"
#include "vec2.h"

#include "SDL2/SDL.h"

class Collide: public Component {
    private:
        SDL_Rect* mCollide;
        float mOffsetX, mOffsetY; // collider position offset from the transform's position

    public:
        Collide();
        Collide(int x, int y, int w, int h);
        Collide(SDL_Rect* rect);
        ~Collide();

        SDL_Rect* getRect();
        Vec2 getScreenPosition();
        Vec2 getScreenSize();

        void setTransformOffset(int x, int y);
        
        void setScreenPosition(int x, int y);
        void setScreenPosition(Vec2 pos);
        void setScreenSize(int w, int h);
        void setScreenSize(Vec2 size);

        bool isColliding(SDL_Rect* rect);
        bool isColliding(Collide* collide);

        void update();
        void render();
};
