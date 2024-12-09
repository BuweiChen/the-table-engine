#include "script.h"

class ArrowTestScript : public Script {
    private:
        float m_dx, m_dy;
    public:
        ArrowTestScript(float dx, float dy);
        void update() override;
};
