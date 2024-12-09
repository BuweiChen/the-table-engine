#pragma once
class GameObject;

#include <functional>
#include <vector>
#include <string>

class SceneNode
{
    friend class SceneTree;
    friend class SceneManager;

    public:
        SceneNode(GameObject* gameObject);

        void addChild(GameObject* child);

        const std::vector<SceneNode*> getChildren();
        SceneNode* getParent();
        GameObject* getGameObject();
        void markForDeletion();
        bool isMarkedForDeletion();

        bool readyToDestroy();
        void setDestroy(bool destroy);

    private:
        SceneNode* m_parent;
        GameObject* m_gameObject;
        std::vector<SceneNode*> m_children;
        bool m_destroy = false;
        ~SceneNode();};

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
