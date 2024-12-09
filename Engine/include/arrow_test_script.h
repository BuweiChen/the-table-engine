#include "script.h"

class ArrowTestScript : public Script {
    private:
        int m_dx, m_dy;
    public:
        ArrowTestScript(int dx, int dy);
        void update() override;
};