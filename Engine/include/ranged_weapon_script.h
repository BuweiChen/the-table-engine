#include "script.h"

class Bow_script : public Script {
    private:
        bool m_shoot;
        int m_lastFireTimeInMs;
        int m_fireRatePerSecond;
        bool m_wasSpacePressed;
        bool m_animationPlayed;

    public:
        Bow_script();
        void input() override;
        void update() override;
};