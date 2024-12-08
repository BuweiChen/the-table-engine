#include "script.h"
#include "collide.h"


class CollideTestScript : public Script {

    private:
        bool m_collide;
    public:
        CollideTestScript();
        void update() override;
        void render() override;
};