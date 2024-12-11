// animationsmanager.cpp
#include "animationsmanager.h"

AnimationsManager::AnimationsManager() : Texture() {
    setName("animationsmanager");
}

AnimationsManager::~AnimationsManager() {
    for (Animation* anim : m_animations) {
        delete anim;
    }
    m_animations.clear();
}

void AnimationsManager::setTexture(SDL_Texture* texture) {
    Texture::setTexture(texture);
    // Propagate texture to all animations
    for (Animation* anim : m_animations) {
        anim->setTexture(texture);
    }
}

void AnimationsManager::setSizeInSpriteMap(int w, int h) {
    Texture::setSizeInSpriteMap(w, h);
    for (Animation* anim : m_animations) {
        anim->setSizeInSpriteMap(w, h);
    }
}

void AnimationsManager::setPositionInSpriteMap(int x, int y) {
    Texture::setPositionInSpriteMap(x, y);
    for (Animation* anim : m_animations) {
        anim->setPositionInSpriteMap(x, y);
    }
}

void AnimationsManager::setFlipHorizontal(bool flip) {
    Texture::setFlipHorizontal(flip);
    for (Animation* anim : m_animations) {
        anim->setFlipHorizontal(flip);
    }
}

void AnimationsManager::setFlipVertical(bool flip) {
    Texture::setFlipVertical(flip);
    for (Animation* anim : m_animations) {
        anim->setFlipVertical(flip);
    }
}

void AnimationsManager::setAngle(float angle) {
    Texture::setAngle(angle);
    for (Animation* anim : m_animations) {
        anim->setAngle(angle);
    }
}

int AnimationsManager::addAnimation(Animation* animation) {
    // Set the owner GameObject to the animation
    animation->setOwner(m_owner);
    m_animations.push_back(animation);
    return static_cast<int>(m_animations.size() - 1);
}

int AnimationsManager::createAnimation(SDL_Texture* texture, int rows, int cols, float time) {
    Animation* animation = new Animation(texture);
    animation->setRowsColsInSpriteMap(rows, cols);
    animation->setAnimationTime(time);
    return addAnimation(animation);
}

void AnimationsManager::setCurrentAnimation(size_t index) {
    if (index < m_animations.size()) {
        m_currentAnimation = index;
    }
}

Animation* AnimationsManager::getCurrentAnimationObject() {
    if (m_animations.empty() || m_currentAnimation >= m_animations.size()) {
        return nullptr;
    }
    return m_animations[m_currentAnimation];
}

void AnimationsManager::play() {
    m_isPlaying = true;
    if (Animation* current = getCurrentAnimationObject()) {
        current->play();
    }
}

void AnimationsManager::pause() {
    m_isPlaying = false;
    if (Animation* current = getCurrentAnimationObject()) {
        current->pause();
    }
}

void AnimationsManager::setFrame(int frame) {
    if (Animation* current = getCurrentAnimationObject()) {
        current->setFrame(frame);
    }
}

int AnimationsManager::getCurrentFrame() const {
    if (m_animations.empty() || m_currentAnimation >= m_animations.size()) {
        return 0;
    }
    return m_animations[m_currentAnimation]->getCurrentFrame();
}

void AnimationsManager::update() {
    if (Animation* current = getCurrentAnimationObject()) {
        current->update();
    }
}

void AnimationsManager::render() {
    if (Animation* current = getCurrentAnimationObject()) {
        current->setOwner(m_owner);  // Ensure owner is set before rendering
        current->render();
    }
}