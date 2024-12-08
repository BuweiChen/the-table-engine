#pragma once

#include "component.h"

#include "SDL2/SDL.h"

class Collide: public Component {
    private:
        SDL_Rect* mCollide;

    public:
        Collide();
        Collide(int x, int y, int w, int h);
        Collide(SDL_Rect* rect);
        ~Collide();

        SDL_Rect* getRect();
        int getPositionX();
        int getPositionY();
        int getSizeW();
        int getSizeH();
        
        void setPositionInScreen(int x, int y);
        void setSizeInScreen(int w, int h);

        void updatePositionInScreen(int dx, int dy);

        bool isColliding(SDL_Rect* rect);
        bool isColliding(Collide* collide);
};