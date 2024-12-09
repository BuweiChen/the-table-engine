#include "script.h"

class Bow_script : public Script {
    private:
        bool m_shoot;
        int m_lastFireTimeInMs;
        int m_fireRatePerSecond;

    public:
        Bow_script();
        void input() override;
        void update() override;
};