#pragma once
class GameObject;

#include <string>

class Script {
    public:
        std::string m_name;
        GameObject* m_owner;

        Script();
        Script(std::string name);
        virtual ~Script();

        std::string getName();
        GameObject* getOwner();
        void setOwner(GameObject* owner);

        virtual void input();
        virtual void update();
        virtual void render();
};