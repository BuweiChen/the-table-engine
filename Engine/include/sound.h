/**
 * @file Sound.h
 * @brief Structure to handle sound effects in the game using SDL_mixer library.
 *
 * This file includes the definition of the Sound structure, which encapsulates
 * sound playing capabilities using the SDL_mixer library, allowing easy management
 * of sound effects including loading, playing, pausing, and volume control.
 */

#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

/**
 * @struct Sound
 * @brief Encapsulates sound management functionality using SDL_mixer.
 *
 * Sound structure provides methods to load, play, stop, pause, and resume sound
 * effects, as well as to adjust their volume. It automatically initializes the
 * SDL_mixer library on construction and cleans up on destruction.
 */
struct Sound {
    Mix_Chunk* m_sound; ///< Pointer to the sound data loaded from a file.

    /**
     * @brief Constructor that initializes the SDL_mixer and loads sound from a specified path.
     * @param path Path to the sound file.
     *
     * The constructor initializes the SDL_mixer with default settings and attempts to load
     * a sound file from the given path. It reports errors if SDL_mixer cannot initialize or
     * the sound file cannot be loaded.
     */
    Sound(std::string path);

    /**
     * @brief Plays the loaded sound.
     * @param loops Number of times the sound should loop; -1 for infinite looping.
     *
     * This method plays the sound using SDL_mixer. The sound can loop multiple times or
     * play indefinitely if specified.
     */
    void play(int loops);

    /**
     * @brief Stops all sound on the channel used by this sound.
     *
     * Stops the playback of the sound by halting the channel it is playing on.
     */
    void stop();

    /**
     * @brief Pauses all sound on the channel used by this sound.
     *
     * Pauses the playback of the sound by pausing the channel it is playing on.
     */
    void pause();

    /**
     * @brief Resumes all paused sound on the channel used by this sound.
     *
     * Resumes the playback of the sound by resuming the paused channel it is playing on.
     */
    void resume();

    /**
     * @brief Sets the volume for the channel used by this sound.
     * @param volume Desired volume level (0 to 128).
     *
     * This method adjusts the volume of the sound channel. The volume range is from 0
     * (mute) to 128 (maximum).
     */
    void setVolume(int volume);

    /**
     * @brief Destructor that frees the loaded sound.
     *
     * The destructor frees the memory allocated for the sound chunk and closes the
     * SDL_mixer to clean up resources.
     */
    ~Sound();
};
