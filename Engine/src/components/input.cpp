#include "input.h"
#include <iostream>

#include <SDL2/SDL.h>

Input::Input()
{
    setName("input");
    m_mouseX = 0;
    m_mouseY = 0;
}

Input::~Input()
{
}

void Input::update()
{
    auto state = SDL_GetKeyboardState(NULL);
    
    spacePressed = state[SDL_SCANCODE_SPACE];
    leftPressed = state[SDL_SCANCODE_LEFT] || state[SDL_SCANCODE_A];
    rightPressed = state[SDL_SCANCODE_RIGHT] || state[SDL_SCANCODE_D];
    upPressed = state[SDL_SCANCODE_UP] || state[SDL_SCANCODE_W];
    downPressed = state[SDL_SCANCODE_DOWN] || state[SDL_SCANCODE_S];

    SDL_GetMouseState(&m_mouseX, &m_mouseY);
    std::cout << "Mouse X: " << m_mouseX << " Mouse Y: " << m_mouseY << std::endl;

    mouseLeftPressed = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT);
    mouseRightPressed = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT);
    mouseMiddlePressed = SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_MIDDLE);
}
