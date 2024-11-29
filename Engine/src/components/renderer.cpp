#include "gameobject.h"
#include "components/transform.cpp"

#include "SDL2/SDL.h"

class Renderer : public Component {
    private:
        SDL_Renderer* mRenderer;
        SDL_Texture* mTexture;

    public:
        Renderer(SDL_Renderer* renderer) {
            mRenderer = renderer;
            mTexture = NULL;
        }

        void SetTexture(SDL_Texture* texture)
        {
            mTexture = texture;
        }

        void SetRenderer(SDL_Renderer* renderer)
        {
            mRenderer = renderer;
        }

        SDL_Renderer* GetRenderer()
        {
            return mRenderer;
        }

        SDL_Texture* GetTexture()
        {
            return mTexture;
        }

        void Render()
        {
            SDL_Rect* rect = m_owner->GetComponent<Transform>()->GetRect();
            SDL_Rect* frame = NULL; // if no frame is specified, render the whole texture

            SDL_RenderCopy(mRenderer, mTexture, frame, rect);
        }
};