#include "script.h"

class ArrowTestScript : public Script {
    private:
        int m_speed = 1;
        int m_dir = 1; // 1 for right, -1 for left
    public:
        ArrowTestScript();
        ArrowTestScript(std::string dir);
        void update();
};
