#include "gameobject.h"
#include "transform.h"
#include "texture.h"
#include "resourcemanager.h"

#include <iostream>

Texture::Texture() {
    setName("texture");
    m_renderer = ResourceManager::getInstance().getRenderer();
    m_texture = NULL;
    m_spriteBox = new SDL_Rect();
    m_spriteClip = new SDL_Rect();

    m_rows = 1;
    m_cols = 1;
    m_time = 1;

    m_flipHorizontal = false;
    m_flipVertical = false;
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

void Texture::setSizeInSpriteMap(int w, int h)
{
    m_spriteBox->w = w;
    m_spriteBox->h = h;
}

void Texture::setPositionInSpriteMap(int x, int y)
{
    m_spriteBox->x = x;
    m_spriteBox->y = y;
}

void Texture::setRowsColsInSpriteMap(int rows, int cols)
{
    m_rows = rows;
    m_cols = cols;
}

void Texture::setAnimationTime(float time)
{
    m_time = time;
}

void Texture::setFlipHorizontal(bool flip)
{
    m_flipHorizontal = flip;
}

void Texture::setFlipVertical(bool flip)
{
    m_flipVertical = flip;
}

void Texture::update()
{
    if (m_rows == 1 && m_cols == 1) 
    {
        m_spriteClip = m_spriteBox;
        return;
    }

    int numFrames = m_rows * m_cols;
    int msPerFrame = m_time * 1000 / numFrames;
    int frame = (SDL_GetTicks() / msPerFrame) % numFrames;

    m_spriteClip->w = m_spriteBox->w / m_cols;
    m_spriteClip->h = m_spriteBox->h / m_rows;
    m_spriteClip->x = (frame % m_cols) * m_spriteClip->w + m_spriteBox->x;
    m_spriteClip->y = (frame / m_cols) * m_spriteClip->h + m_spriteBox->y;
}

void Texture::render()
{
    SDL_Rect* rect = m_owner->getComponent<Transform>()->getScreenRect();

    int hFlip = (m_flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    int vFlip = (m_flipVertical ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    SDL_RendererFlip flip = (SDL_RendererFlip) (hFlip | vFlip);

    SDL_RenderCopyEx(m_renderer, m_texture, m_spriteClip, rect, 0, NULL, flip);
}
