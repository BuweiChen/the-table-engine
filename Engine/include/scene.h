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

        void addChild(GameObject* child, bool isBackground = false);

        const std::vector<SceneNode*> getChildren();
        SceneNode* getParent();
        GameObject* getGameObject();

        bool readyToDestroy();
        void setDestroy(bool destroy);
        
        bool isBackground();    
        void setIsBackground(bool isBackground);

    private:
        SceneNode* m_parent;
        GameObject* m_gameObject;
        std::vector<SceneNode*> m_children;

        bool m_destroy = false;
        bool m_isBackground = false;

        ~SceneNode();};

class SceneTree
{
    public:
        SceneTree();
        ~SceneTree();

        void addChild(GameObject* child, bool isBackground = false);

        void traverseTree(std::function<void(SceneNode*)> callback);
        void traverseTree(SceneNode* node, std::function<void(SceneNode*)> callback);

        GameObject* findGameObjectById(std::string id);
        std::vector<GameObject*> findGameObjectsByTag(std::string tag);

    private:
        SceneNode* m_root;
        std::unordered_map<std::string, GameObject*> m_cachedGameObjects; // cache for faster lookup

        /**
         * optional: add frame specific cache for faster lookup of other objects (not just player)
         */
};
