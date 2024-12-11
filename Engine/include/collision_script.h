#include "script.h"
#include "collide.h"


class CollisionScript : public Script {

    private:
        bool m_collide;
    public:
        CollisionScript();
        void update() override;
        void render() override;
};