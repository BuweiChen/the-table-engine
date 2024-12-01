#include "gameobject.h"
#include "transform.h"
#include "texture.h"
#include "resourcemanager.h"

Texture::Texture() {
    setName("texture");
    m_renderer = ResourceManager::getInstance().getRenderer();
    m_texture = NULL;
}

Texture::Texture(SDL_Texture* texture) : Texture() {
    m_texture = texture;
}

SDL_Texture* Texture::getTexture()
{
    return m_texture;
}

void Texture::setTexture(SDL_Texture* texture)
{
    m_texture = texture;
}

void Texture::render()
{
    SDL_Rect* rect = m_owner->getComponent<Transform>()->getRect();
    SDL_Rect* frame = NULL; // NULL means render the entire texture

    SDL_RenderCopy(m_renderer, m_texture, frame, rect);
}
