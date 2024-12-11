#include "script.h"

class RangedWeaponScript : public Script {
    private:
        bool m_shoot;
        int m_lastFireTimeInMs;
        int m_fireRatePerSecond;
        bool m_wasSpacePressed;
        bool m_animationPlayed;

    public:
        RangedWeaponScript();
        void input() override;
        void update() override;
};