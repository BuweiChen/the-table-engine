#pragma once

#include <string>
#include "SDL2/SDL.h"

/**
 * @file gameapplication.h
 * @brief Defines the GameApplication structure for managing the main game loop and rendering.
 *
 * This structure encapsulates the core functionalities required for initializing the game,
 * managing the game loop, handling user input, updating game state, and rendering.
 */

/**
 * @struct GameApplication
 * @brief Manages the main game loop, rendering, and application state.
 *
 * GameApplication is responsible for setting up the SDL window and renderer,
 * and it controls the main execution loop of the game. It also handles basic performance
 * statistics like FPS and provides mechanisms for game state updates and rendering.
 */
struct GameApplication {
    SDL_Window* m_window = NULL; ///< Pointer to the SDL_Window.
    SDL_Renderer* m_renderer = NULL; ///< Pointer to the SDL_Renderer used for all rendering in the game.

    bool m_gameIsRunning = true; ///< Flag to control the game loop.

    float m_FPS = 0; ///< Frames per second, updated during the game loop to measure performance.

    /**
     * @brief Constructs a GameApplication with a specified window title.
     * @param title The title for the game window.
     */
    GameApplication(std::string title);

    /**
     * @brief Destructor that cleans up SDL resources.
     */
    ~GameApplication();

    /**
     * @brief Prints current game statistics like FPS.
     */
    void printStats();

    /**
     * @brief Starts the game application, initializing all necessary resources.
     */
    void start(bool demo); 

    /**
     * @brief Processes input from the user.
     * This function should be called in the game loop to handle events like keystrokes and mouse movements.
     */
    void input();

    /**
     * @brief Updates the game state.
     * This function should be called once per frame to update the state of the game, including game objects.
     */
    void update();

    /**
     * @brief Renders the game state to the window.
     * This function should be called once per frame to draw all game visuals.
     */
    void render();

    /**
     * @brief Advances the game frame, updating timing and FPS calculations.
     */
    void advanceFrame();

    /**
     * @brief The main game loop that runs continuously while the game is active.
     * This loop calls the input, update, and render functions in sequence.
     */
    void runLoop();
};
