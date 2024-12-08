#pragma once 

#include "script.h"

class PlayerTestScript : public Script {
    public:
        PlayerTestScript(std::string name);
        ~PlayerTestScript();

        void update() override;
};
