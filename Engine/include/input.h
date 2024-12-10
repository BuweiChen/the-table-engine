#pragma once

#include "component.h"

/**
 * @file input.h
 * @brief Defines the Input component for handling input operations in the game engine.
 *
 * This component captures and stores the state of various input devices such as keyboard and mouse,
 * making it accessible to other components and systems within the engine.
 */

/**
 * @class Input
 * @brief Component for handling and storing the state of input devices.
 *
 * The Input class extends the Component class and is used to track the state of various keys and mouse buttons,
 * as well as the mouse's position, providing a centralized way to handle user interactions.
 */
class Input : public Component {
public:
    bool spacePressed = false; ///< True if the space bar is pressed, false otherwise.

    bool leftPressed = false; ///< True if the left arrow key is pressed, false otherwise.
    bool rightPressed = false; ///< True if the right arrow key is pressed, false otherwise.
    bool upPressed = false; ///< True if the up arrow key is pressed, false otherwise.
    bool downPressed = false; ///< True if the down arrow key is pressed, false otherwise.

    int m_mouseX, m_mouseY; ///< Current position of the mouse cursor.

    bool mouseLeftPressed = false; ///< True if the left mouse button is pressed, false otherwise.
    bool mouseRightPressed = false; ///< True if the right mouse button is pressed, false otherwise.
    bool mouseMiddlePressed = false; ///< True if the middle mouse button is pressed, false otherwise.

    /**
     * @brief Constructor for the Input component.
     */
    Input();

    /**
     * @brief Destructor for the Input component.
     */
    ~Input();

    /**
     * @brief Updates the state of the input based on the latest user interactions.
     * 
     * This method should be called every frame to update the input states (e.g., which keys are pressed).
     */
    void update() override;
};
