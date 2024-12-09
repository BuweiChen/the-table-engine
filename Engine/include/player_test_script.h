#pragma once 

#include "script.h"

class PlayerTestScript : public Script {
    private:
        int m_fireRatePerSecond = 5; 
        int m_lastFireTimeInMs = 0; // to meet fire rate condition

        float m_playerSpeed = 6;
        int m_keysCollected = 0;
    public:
        PlayerTestScript();
        int getKeysCollected();

        void update() override;
};
