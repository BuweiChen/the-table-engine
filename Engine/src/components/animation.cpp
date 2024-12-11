#include "animation.h"

Animation::Animation() : Texture() {
    setName("animation");
    m_startTime = SDL_GetTicks();
    m_isPlaying = true;
}

Animation::Animation(SDL_Texture* texture) : Texture(texture) {
    setName("animation");
    m_startTime = SDL_GetTicks();
    m_isPlaying = true;
}

int Animation::getRows() {
    return m_rows;
}

int Animation::getCols() {
    return m_cols;
}

int Animation::getNumFrames() {
    return m_numFrames;
}

void Animation::setAutoPlay(bool autoplay) {
    m_isPlaying = autoplay;
    if (autoplay) {
        m_startTime = SDL_GetTicks();
    }
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

void Animation::play() {
    if (!m_isPlaying) {
        m_isPlaying = true;
        m_startTime = SDL_GetTicks();
    }
}

void Animation::pause() {
    if (m_isPlaying) {
        m_isPlaying = false;
        m_pausedTime = SDL_GetTicks();
    }
}

void Animation::setFrame(int frame) {
    m_currentFrame = frame % m_numFrames;
    
    m_spriteClip->w = m_spriteBox->w / m_cols;
    m_spriteClip->h = m_spriteBox->h / m_rows;
    m_spriteClip->x = (m_currentFrame % m_cols) * m_spriteClip->w + m_spriteBox->x;
    m_spriteClip->y = (m_currentFrame / m_cols) * m_spriteClip->h + m_spriteBox->y;
}

void Animation::update() {
    if (m_numFrames == 1) {
        m_spriteClip->x = m_spriteBox->x;
        m_spriteClip->y = m_spriteBox->y;
        m_spriteClip->w = m_spriteBox->w;
        m_spriteClip->h = m_spriteBox->h;
        return;
    }

    if (m_isPlaying) {
        int elapsedTime = SDL_GetTicks() - m_startTime;
        m_currentFrame = (elapsedTime / m_msPerFrame) % m_numFrames;
    }

    m_spriteClip->w = m_spriteBox->w / m_cols;
    m_spriteClip->h = m_spriteBox->h / m_rows;
    m_spriteClip->x = (m_currentFrame % m_cols) * m_spriteClip->w + m_spriteBox->x;
    m_spriteClip->y = (m_currentFrame / m_cols) * m_spriteClip->h + m_spriteBox->y;
}