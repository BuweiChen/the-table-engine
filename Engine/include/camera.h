#pragma once

#include "component.h"
#include "vec2.h"

class Camera : public Component {
    public:
        Camera();
        ~Camera();

        void update();

        Vec2 getWorldPosition();
        void setWorldPosition(float x, float y);
    
    private:
        Vec2 m_worldPosition;
};
