#include "gameobject.h"

class GameObjectFactory {
    public:
        static GameObject* createPlayerTest();
        static GameObject* createAxe();
        static GameObject* createEnemyWarriorDying();
};
