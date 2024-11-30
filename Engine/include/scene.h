#pragma once
class GameObject;

#include <functional>
#include <vector>

class SceneNode
{
    public:
        SceneNode(GameObject* gameObject);
        ~SceneNode();

        void addChild(GameObject* child);
        bool removeChild(std::string id);

        std::vector<SceneNode*> getChildren();
        SceneNode* getParent();
        GameObject* getGameObject();

    private:
        SceneNode* m_parent;
        GameObject* m_gameObject;
        std::vector<SceneNode*> m_children;
};

class SceneTree
{
    public:
        SceneTree();
        ~SceneTree();

        void addChild(GameObject* child);

        void traverseTree(std::function<void(SceneNode*)> callback);
        void traverseTree(SceneNode* node, std::function<void(SceneNode*)> callback);

        GameObject* findGameObjectById(std::string id);
        std::vector<GameObject*> findGameObjectsByTag(std::string tag);

    private:
        SceneNode* m_root;
};
