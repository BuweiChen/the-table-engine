#pragma once 

#include "script.h"

class PlayerInputScript : public Script {
    private:
        int m_fireRatePerSecond = 5; 
        int m_lastFireTimeInMs = 0; // to meet fire rate condition

        float m_playerSpeed = 6;
        int m_keysCollected = 0;
    public:
        PlayerInputScript();
        int getKeysCollected();

        void update() override;
};
