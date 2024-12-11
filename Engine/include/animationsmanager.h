// animationsmanager.h
#pragma once

#include "texture.h"
#include "animation.h"
#include <vector>
#include <string>

class AnimationsManager : public Texture {
protected:
    std::vector<Animation*> m_animations;
    size_t m_currentAnimation = 0;
    bool m_isPlaying = true;

public:
    AnimationsManager();
    ~AnimationsManager();

    int addAnimation(Animation* animation);
    int createAnimation(SDL_Texture* texture, int rows, int cols, float time);
    void setCurrentAnimation(size_t index);
    size_t getCurrentAnimation() const { return m_currentAnimation; }
    Animation* getCurrentAnimationObject();
    void play();
    void pause();
    void setFrame(int frame);
    int getCurrentFrame() const;
    bool isPlaying() const { return m_isPlaying; }
    void update() override;
    void render() override;

    // Now these can properly override the virtual methods from Texture
    void setTexture(SDL_Texture* texture) override;
    void setSizeInSpriteMap(int w, int h) override;
    void setPositionInSpriteMap(int x, int y) override;
    void setFlipHorizontal(bool flip) override;
    void setFlipVertical(bool flip) override;
    void setAngle(float angle) override;
};