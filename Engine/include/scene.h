#pragma once

#include <functional>
#include <vector>
#include <string>
#include <unordered_map>
class GameObject;

/**
 * @file scene.h
 * @brief Defines the SceneNode and SceneTree classes for managing game objects within scenes.
 *
 * This file outlines the structure and functionality of the SceneNode and SceneTree classes,
 * which are used to organize and manage game objects within the scenes of the game engine.
 */

/**
 * @class SceneNode
 * @brief Represents a node in the scene graph, encapsulating a game object and its hierarchy.
 *
 * SceneNode provides functionality to manage a hierarchy of game objects, including adding children,
 * managing lifecycle states, and setting background status.
 */
class SceneNode
{
    friend class SceneTree;
    friend class SceneManager;

public:
    /**
     * @brief Constructor that assigns a game object to this node.
     * @param gameObject Pointer to the GameObject associated with this node.
     */
    SceneNode(GameObject* gameObject);

    /**
     * @brief Adds a child game object to this node.
     * @param child Pointer to the child GameObject to add.
     * @param isBackground Flag indicating if the child is part of the background.
     */
    void addChild(GameObject* child, bool isBackground = false);

    /**
     * @brief Returns the children of this node.
     * @return Vector of pointers to the child SceneNodes.
     */
    const std::vector<SceneNode*> getChildren();

    /**
     * @brief Gets the parent of this node.
     * @return Pointer to the parent SceneNode.
     */
    SceneNode* getParent();

    /**
     * @brief Gets the GameObject associated with this node.
     * @return Pointer to the GameObject.
     */
    GameObject* getGameObject();

    /**
     * @brief Checks if this node is marked for destruction.
     * @return True if marked for destruction, false otherwise.
     */
    bool readyToDestroy();

    /**
     * @brief Sets the destruction state of this node.
     * @param destroy Flag indicating whether to mark this node for destruction.
     */
    void setDestroy(bool destroy);
    
    /**
     * @brief Checks if this node is part of the background.
     * @return True if it is background, false otherwise.
     */
    bool isBackground();    

    /**
     * @brief Sets whether this node is part of the background.
     * @param isBackground Flag indicating background status.
     */
    void setIsBackground(bool isBackground);

private:
    SceneNode* m_parent;
    GameObject* m_gameObject;
    std::vector<SceneNode*> m_children;

    bool m_destroy = false;
    bool m_isBackground = false;

    /**
     * @brief Destructor, ensures proper cleanup of node resources.
     */
    ~SceneNode();
};

/**
 * @class SceneTree
 * @brief Manages a tree structure of SceneNodes, facilitating scene graph operations.
 *
 * SceneTree provides mechanisms to add children, traverse the tree, and perform lookups
 * for game objects based on IDs and tags.
 */
class SceneTree
{
public:
    /**
     * @brief Constructor for creating a root node of the scene tree.
     */
    SceneTree();

    /**
     * @brief Destructor, cleans up the tree resources.
     */
    ~SceneTree();

    /**
     * @brief Adds a child GameObject to the scene tree.
     * @param child Pointer to the GameObject to add.
     * @param isBackground Flag indicating if the child is part of the background.
     */
    void addChild(GameObject* child, bool isBackground = false);

    /**
     * @brief Traverses the entire tree, executing a callback on each node.
     * @param callback Function to execute for each node.
     */
    void traverseTree(std::function<void(SceneNode*)> callback);

    /**
     * @brief Traverses the tree from a specific node, executing a callback on each node.
     * @param node Starting node for traversal.
     * @param callback Function to execute for each node.
     */
    void traverseTree(SceneNode* node, std::function<void(SceneNode*)> callback);

    /**
     * @brief Finds a GameObject by its ID.
     * @param id The ID string of the GameObject to find.
     * @return Pointer to the GameObject if found, nullptr otherwise.
     */
    GameObject* findGameObjectById(std::string id);

    /**
     * @brief Finds GameObjects by a tag.
     * @param tag The tag string to search for.
     * @return Vector of GameObjects with the specified tag.
     */
    std::vector<GameObject*> findGameObjectsByTag(std::string tag);

private:
    SceneNode* m_root;
    std::unordered_map<std::string, GameObject*> m_cachedGameObjects; // Cache for faster lookup of GameObjects.
};
