#include "animation.h"
#include "transform.h"
#include "gameobject.h"

Animation::Animation() : Texture() {
    setName("animation");
    m_spriteBox = new SDL_Rect();
    m_spriteClip = new SDL_Rect();
    
    m_rows = 1;
    m_cols = 1;
    m_time = 1;

    m_numFrames = m_rows * m_cols;
    m_msPerFrame = m_time * 1000 / m_numFrames;
}

Animation::Animation(SDL_Texture* texture) : Animation() {
    setTexture(texture);
}

Animation::~Animation() {
    delete m_spriteBox;
    delete m_spriteClip;
}

void Animation::setSizeInSpriteMap(int w, int h) {
    m_spriteBox->w = w;
    m_spriteBox->h = h;
    update();
}

void Animation::setPositionInSpriteMap(int x, int y) {
    m_spriteBox->x = x;
    m_spriteBox->y = y;
    update();
}

void Animation::setRowsColsInSpriteMap(int rows, int cols) {
    m_rows = rows;
    m_cols = cols;
    m_numFrames = m_rows * m_cols;
    m_msPerFrame = m_time * 1000 / m_numFrames;
    update();
}

void Animation::setAnimationTime(float time) {
    m_time = time;
    m_msPerFrame = m_time * 1000 / m_numFrames;
}

void Animation::update() {
    if (m_numFrames == 1) {
        m_spriteClip->x = m_spriteBox->x;
        m_spriteClip->y = m_spriteBox->y;
        m_spriteClip->w = m_spriteBox->w;
        m_spriteClip->h = m_spriteBox->h;
        return;
    }

    int frame = (SDL_GetTicks() / m_msPerFrame) % m_numFrames;

    m_spriteClip->w = m_spriteBox->w / m_cols;
    m_spriteClip->h = m_spriteBox->h / m_rows;
    m_spriteClip->x = (frame % m_cols) * m_spriteClip->w + m_spriteBox->x;
    m_spriteClip->y = (frame / m_cols) * m_spriteClip->h + m_spriteBox->y;
}

void Animation::render() {
    if (!m_texture) return;

    SDL_Rect* rect = m_owner->getComponent<Transform>()->getScreenRect();
    if (rect->x + rect->w < 0 || rect->x > 640 || rect->y + rect->h < 0 || rect->y > 480) 
        return;

    int hFlip = (m_flipHorizontal ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE);
    int vFlip = (m_flipVertical ? SDL_FLIP_VERTICAL : SDL_FLIP_NONE);
    SDL_RendererFlip flip = (SDL_RendererFlip) (hFlip | vFlip);

    SDL_RenderCopyEx(m_renderer, m_texture, m_spriteClip, rect, m_angle, NULL, flip);
}