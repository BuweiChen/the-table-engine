#include "component.h"

#include "SDL2/SDL.h"

class Transform : public Component {
    private:
        SDL_Rect* mTransform;

    public:
        Transform()
        {
            mTransform = new SDL_Rect();
        }

        Transform(int x, int y)
        {
            mTransform = new SDL_Rect();
            mTransform->x = x;
            mTransform->y = y;
        }

        ~Transform()
        {
            delete mTransform;
        }

        SDL_Rect* GetRect()
        {
            return mTransform;
        }

        int GetPositionX()
        {
            return mTransform->x;
        }

        int GetPositionY()
        {
            return mTransform->y;
        }

        int GetSizeW()
        {
            return mTransform->w;
        }

        int GetSizeH()
        {
            return mTransform->h;
        }

        void SetPosition(int x, int y)
        {
            mTransform->x = x;
            mTransform->y = y;
        }

        void SetSize(int w, int h)
        {
            mTransform->w = w;
            mTransform->h = h;
        }
};