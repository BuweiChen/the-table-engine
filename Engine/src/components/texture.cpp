#include "texture.h"
#include "gameobject.h"
#include "resourcemanager.h"

Texture::Texture() {
    setName("texture");
    m_renderer = ResourceManager::getInstance().getRenderer();
    m_texture = NULL;
    m_spriteBox = new SDL_Rect();
    m_spriteClip = new SDL_Rect();
}

Texture::Texture(SDL_Texture* texture) : Texture() {
    setTexture(texture);
}

SDL_Texture* Texture::getTexture() {
    return m_texture;
}

void Texture::setTexture(SDL_Texture* texture) {
    m_texture = texture;
    SDL_QueryTexture(m_texture, NULL, NULL, &m_spriteBox->w, &m_spriteBox->h);
    m_spriteBox->x = 0;
    m_spriteBox->y = 0;
    
    // Initialize sprite clip to full texture
    *m_spriteClip = *m_spriteBox;
}

void Texture::setSizeInSpriteMap(int w, int h) {
    m_spriteBox->w = w;
    m_spriteBox->h = h;
    *m_spriteClip = *m_spriteBox;
}

void Texture::setPositionInSpriteMap(int x, int y) {
    m_spriteBox->x = x;
    m_spriteBox->y = y;
    *m_spriteClip = *m_spriteBox;
}

void Texture::setFlipHorizontal(bool flip) {
    m_flipHorizontal = flip;
}

void Texture::setFlipVertical(bool flip) {
    m_flipVertical = flip;
}

void Texture::update() {
    // Base texture doesn't need updating
}

void Texture::render() {
    SDL_Rect* rect = m_owner->getComponent<Transform>()->getScreenRect();
    if (rect->x + rect->w < 0 || rect->x > 640 || rect->y + rect->h < 0 || rect->y > 480) 
        return;

    int hFlip = (m_flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    int vFlip = (m_flipVertical ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    SDL_RendererFlip flip = (SDL_RendererFlip)(hFlip | vFlip);

    SDL_RenderCopyEx(m_renderer, m_texture, m_spriteClip, rect, m_angle, NULL, flip);
}