#include "gameobject.h"

class GameObjectFactory {
    public:
        static GameObject* createPlayerTest();
        static GameObject* createBow();
        static GameObject* createEnemyWarriorDying();
};
