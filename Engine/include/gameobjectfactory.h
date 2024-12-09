#include "gameobject.h"
#include <string>

class GameObjectFactory {
    public:
        static GameObject* createPlayerTest();
        static GameObject* createBow();
        static GameObject* createArrow(int dx, int dy);
        static GameObject* createEnemyWarrior();
};
