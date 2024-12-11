#include "script.h"

class ProjectileScript : public Script {
    private:
        float m_dx, m_dy;
    public:
        ProjectileScript(float dx, float dy);
        void update() override;
};
