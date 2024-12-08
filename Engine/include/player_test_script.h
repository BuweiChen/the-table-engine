#pragma once 

#include "script.h"

class PlayerTestScript : public Script {
    private:
        int m_fireRatePerSecond = 5; 
        int m_lastFireTimeInMs = 0; // to meet fire rate condition
    public:
        PlayerTestScript();
        void update() override;
};