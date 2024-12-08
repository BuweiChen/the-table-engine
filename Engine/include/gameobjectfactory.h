#include "gameobject.h"
#include <string>

class GameObjectFactory {
    public:
        static GameObject* createPlayerTest();
        static GameObject* createBow();
        static GameObject* createArrow(std::string direction);
        static GameObject* createEnemyWarrior();
};
