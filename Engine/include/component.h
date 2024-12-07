#pragma once
class GameObject;

#include <string>

class Component
{
    protected:
        std::string m_name;
        GameObject* m_owner; // game object that owns this component

    public:
        Component();
        Component(std::string name);
        virtual ~Component();

        std::string getName();
        GameObject* getOwner();
        void setName(std::string name);
        void setOwner(GameObject* owner);

        void input();
        virtual void update();
        virtual void render();
};
