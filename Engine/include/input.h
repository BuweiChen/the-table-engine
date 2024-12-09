#pragma once

#include "component.h"

class Input : public Component {
    public:
        bool spacePressed = false;

        bool leftPressed = false;
        bool rightPressed = false;
        bool upPressed = false;
        bool downPressed = false;

        int m_mouseX, m_mouseY;

        bool mouseLeftPressed = false;
        bool mouseRightPressed = false;
        bool mouseMiddlePressed = false;

        Input();
        ~Input();

        void update() override;
};
