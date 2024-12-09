#include "script.h"

class EnemyAIScript : public Script {
    private:
        float m_speed = 2;
    public:
        EnemyAIScript();
        void update() override;
};
