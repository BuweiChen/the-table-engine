#include "gameobject.h"
#include "transform.h"
#include "renderer.h"

Renderer::Renderer(SDL_Renderer* renderer) {
    setName("renderer");
    m_renderer = renderer;
    m_texture = NULL;
}

void Renderer::setTexture(SDL_Texture* texture)
{
    m_texture = texture;
}

void Renderer::setRenderer(SDL_Renderer* renderer)
{
    m_renderer = renderer;
}

SDL_Renderer* Renderer::getRenderer()
{
    return m_renderer;
}

SDL_Texture* Renderer::getTexture()
{
    return m_texture;
}

void Renderer::render()
{
    SDL_Rect* rect = m_owner->getComponent<Transform>()->getRect();
    SDL_Rect* frame = NULL; // NULL means render the entire texture

    SDL_RenderCopy(m_renderer, m_texture, frame, rect);
}
