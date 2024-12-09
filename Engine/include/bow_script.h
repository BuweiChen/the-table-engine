#include "script.h"

class Bow_script : public Script {
    private:
        bool m_shoot;

    public:
        Bow_script();
        void input() override;
        void update() override;
};