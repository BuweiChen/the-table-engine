#pragma once
class GameObject;

#include <string>

class Script {
    public:
        std::string m_name;
        GameObject* m_owner;

        Script(std::string name);
        virtual ~Script();

        std::string getName();
        GameObject* getOwner();
        void setOwner(GameObject* owner);

        void input();
        void update();
        void render();
};