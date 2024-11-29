#pragma once

#include "component.h"

#include "SDL2/SDL.h"

class Transform : public Component {
    private:
        SDL_Rect* mTransform;

    public:
        Transform();
        Transform(int x, int y);
        ~Transform();

        SDL_Rect* getRect();
        int getPositionX();
        int getPositionY();
        int getSizeW();
        int getSizeH();
        
        void setPosition(int x, int y);
        void setSize(int w, int h);
};