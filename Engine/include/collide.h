#pragma once

#include "component.h"
#include "vec2.h"

#include "SDL2/SDL.h"

class Collide: public Component {
    private:
        SDL_Rect* mCollide; // relative to the screen

        float mOffsetX, mOffsetY; // collider position offset from the transform's position
        SDL_Rect* nextRect(float dx, float dy); // next frame's collider position

    public:
        Collide();
        ~Collide();

        SDL_Rect* getRect();

        Vec2 getScreenPosition();
        Vec2 getScreenSize();

        // updates velocities in-place to prevent collision with another collide
        void preventCollision(Collide* anotherCollide, float& dx, float& dy);

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
