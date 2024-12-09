#pragma once 

#include "script.h"

class PlayerTestScript : public Script {
    private:
        int m_fireRatePerSecond = 5; 
        int m_lastFireTimeInMs = 0; // to meet fire rate condition

        float m_playerSpeed = 6;
    public:
        PlayerTestScript();
        void update() override;
};
