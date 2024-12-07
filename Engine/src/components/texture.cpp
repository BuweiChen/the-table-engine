#include "gameobject.h"
#include "transform.h"
#include "texture.h"
#include "resourcemanager.h"

Texture::Texture() {
    setName("texture");
    m_renderer = ResourceManager::getInstance().getRenderer();
    m_texture = NULL;
    m_spriteBox = new SDL_Rect();
}

Texture::Texture(SDL_Texture* texture) : Texture() {
    setTexture(texture);
}

SDL_Texture* Texture::getTexture()
{
    return m_texture;
}

void Texture::setTexture(SDL_Texture* texture)
{
    m_texture = texture;
    SDL_QueryTexture(m_texture, NULL, NULL, &m_spriteBox->w, &m_spriteBox->h);
    m_spriteBox->x = 0;
    m_spriteBox->y = 0;
}

void Texture::render()
{
    SDL_Rect* rect = m_owner->getComponent<Transform>()->getRect();
    SDL_RenderCopy(m_renderer, m_texture, m_spriteBox, rect);
}
