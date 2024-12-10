#pragma once

class GameObject;

#include <string>

/**
 * @file component.h
 * @brief Defines the Component base class for all components in the game engine.
 *
 * This file contains the definition of the Component class, which serves as the base class
 * for all components that can be attached to game objects. Components encapsulate behavior
 * and state that can be managed by game objects.
 */

/**
 * @class Component
 * @brief Base class for all game components, providing basic component functionalities.
 *
 * This class defines the interface and common functionalities for all components
 * that can be attached to GameObjects. Components can manipulate or extend the
 * capabilities of GameObjects by overriding input, update, and render methods.
 */
class Component
{
protected:
    std::string m_name; ///< Name of the component, useful for identification or debugging.
    GameObject* m_owner; ///< Pointer to the GameObject that owns this component.

public:
    /**
     * @brief Default constructor for the Component.
     */
    Component();

    /**
     * @brief Constructs a Component with a specified name.
     * @param name Name of the component.
     */
    Component(std::string name);

    /**
     * @brief Virtual destructor for safe polymorphic use.
     */
    virtual ~Component();

    /**
     * @brief Retrieves the name of the component.
     * @return The name of the component as a std::string.
     */
    std::string getName();

    /**
     * @brief Retrieves the GameObject that owns this component.
     * @return Pointer to the owning GameObject.
     */
    GameObject* getOwner();

    /**
     * @brief Sets the name of the component.
     * @param name New name for the component.
     */
    void setName(std::string name);

    /**
     * @brief Sets the GameObject owner of this component.
     * @param owner Pointer to the GameObject to become the new owner.
     */
    void setOwner(GameObject* owner);

    /**
     * @brief Virtual method for handling input, intended to be overridden by derived components.
     */
    virtual void input();

    /**
     * @brief Virtual method for updating the component's state, intended to be overridden by derived components.
     */
    virtual void update();

    /**
     * @brief Virtual method for rendering, intended to be overridden by derived components.
     */
    virtual void render();
};
