#pragma once
class GameObject;

#include <string>

class Script {
    public:
        std::string m_name;
        GameObject* m_owner;

        Script(std::string name);
        virtual ~Script();

        std::string GetName();
        GameObject* GetOwner();
        void SetOwner(GameObject* owner);

        void Input();
        void Update();
        void Render();
};