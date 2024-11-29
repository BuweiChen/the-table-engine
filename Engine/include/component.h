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
        ~Component();

        std::string GetName();
        GameObject* GetOwner();
        void SetName(std::string name);
        void SetOwner(GameObject* owner);

        void Input();
        void Update();
        void Render();
};
