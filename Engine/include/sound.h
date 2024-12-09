#pragma once

#include <string>
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

struct Sound {
    Sound(std::string path) {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
            std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        }       

        m_sound = Mix_LoadWAV(path.c_str());
        if (m_sound == NULL) {
            std::cout << "Error loading sound: " << path << std::endl;
        }
    }

    void play(int loops) {
        Mix_PlayChannel(-1, m_sound, loops);
    }

    void stop() {
        Mix_HaltChannel(-1);
    }

    void pause() {
        Mix_Pause(-1);
    }

    void resume() {
        Mix_Resume(-1);
    }

    void setVolume(int volume) {
        Mix_Volume(-1, volume);
    }

    ~Sound() {
        Mix_FreeChunk(m_sound);
    }

    Mix_Chunk* m_sound;
};
