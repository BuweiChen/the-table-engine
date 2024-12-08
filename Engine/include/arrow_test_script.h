#include "script.h"

class ArrowTestScript : public Script {
    private:
        int m_speed = 1;
    public:
        ArrowTestScript();
        void update() override;
};
