#include "engine/Input.h"
#include <SDL.h>

using namespace engine;

int Input::mouseX;
int Input::mouseY;

uint16_t Input::keysBuffer;
uint16_t Input::prevKeysBuffer;
uint8_t Input::mouseBuffer;

int Input::GetMouseX()
{
    return mouseX;
}

int Input::GetMouseY()
{
    return mouseY;
}

void Input::Capture()
{
    prevKeysBuffer = keysBuffer;

    for (SDL_Event e; SDL_PollEvent(&e);)
    {
        if (e.type == SDL_QUIT)
            keysBuffer |= KEY_QUIT;

        else if (e.type == SDL_KEYDOWN)
        {
            if (e.key.keysym.sym == SDLK_q &&
                e.key.keysym.mod == KMOD_LCTRL)
                keysBuffer |= KEY_QUIT;

            switch (e.key.keysym.sym)
            {
                case SDLK_q:
                    keysBuffer |= KEY_Q;
                    break;

                case SDLK_w:
                    keysBuffer |= KEY_W;
                    break;

                case SDLK_e:
                    keysBuffer |= KEY_E;
                    break;

                case SDLK_a:
                    keysBuffer |= KEY_A;
                    break;

                case SDLK_d:
                    keysBuffer |= KEY_D;
                    break;

                case SDLK_p:
                    keysBuffer |= KEY_P;
                    break;

                case SDLK_LEFTBRACKET:
                    keysBuffer |= KEY_L_BRACKET;
                    break;

                case SDLK_RIGHTBRACKET:
                    keysBuffer |= KEY_R_BRACKET;
                    break;

                case SDLK_LEFT:
                    keysBuffer |= KEY_LEFT;
                    break;

                case SDLK_RIGHT:
                    keysBuffer |= KEY_RIGHT;
                    break;

                case SDLK_z:
                    keysBuffer |= KEY_Z;
                    break;

                case SDLK_F1:
                    keysBuffer |= KEY_F1;
                    break;

                case SDLK_SPACE:
                    keysBuffer |= KEY_SPACE;
                    break;

                default:
                    break;
            }
        }

        else if (e.type == SDL_KEYUP)
        {
            switch (e.key.keysym.sym)
            {
                case SDLK_q:
                    keysBuffer &= ~KEY_Q;
                    break;

                case SDLK_w:
                    keysBuffer &= ~KEY_W;
                    break;

                case SDLK_e:
                    keysBuffer &= ~KEY_E;
                    break;

                case SDLK_a:
                    keysBuffer &= ~KEY_A;
                    break;

                case SDLK_d:
                    keysBuffer &= ~KEY_D;
                    break;

                case SDLK_p:
                    keysBuffer &= ~KEY_P;
                    break;

                case SDLK_LEFTBRACKET:
                    keysBuffer &= ~KEY_L_BRACKET;
                    break;

                case SDLK_RIGHTBRACKET:
                    keysBuffer &= ~KEY_R_BRACKET;
                    break;

                case SDLK_LEFT:
                    keysBuffer &= ~KEY_LEFT;
                    break;

                case SDLK_RIGHT:
                    keysBuffer &= ~KEY_RIGHT;
                    break;

                case SDLK_z:
                    keysBuffer &= ~KEY_Z;
                    break;

                case SDLK_F1:
                    keysBuffer &= ~KEY_F1;
                    break;

                case SDLK_SPACE:
                    keysBuffer &= ~KEY_SPACE;
                    break;

                default:
                    break;
            }
        }

        else if (e.type == SDL_MOUSEBUTTONDOWN)
        {
            switch (e.button.button)
            {
                case SDL_BUTTON_LEFT:
                    mouseBuffer |= BUTTON_LEFT;
                    break;

                case SDL_BUTTON_RIGHT:
                    mouseBuffer |= BUTTON_RIGHT;
                    break;

                case SDL_BUTTON_MIDDLE:
                    mouseBuffer |= BUTTON_MIDDLE;

                default:
                    break;
            }
        }

        else if (e.type == SDL_MOUSEBUTTONUP)
        {
            switch (e.button.button)
            {
                case SDL_BUTTON_LEFT:
                    mouseBuffer &= ~BUTTON_LEFT;
                    break;

                case SDL_BUTTON_RIGHT:
                    mouseBuffer &= ~BUTTON_RIGHT;
                    break;

                case SDL_BUTTON_MIDDLE:
                    mouseBuffer &= ~BUTTON_MIDDLE;

                default:
                    break;
            }
        }

        else if (e.type == SDL_MOUSEMOTION)
        {
            mouseX = e.motion.x;
            mouseY = e.motion.y;
        }
    }
}

bool Input::KeyPressed(uint16_t key)
{
    return (bool)(keysBuffer & key);
}

bool Input::KeyTyped(uint16_t key)
{
    bool keyPressed = (bool)(keysBuffer & key);
    bool prevKeyPressed = (bool)(prevKeysBuffer & key);

    return keyPressed && !prevKeyPressed;
}

bool Input::ButtonPressed(uint8_t button)
{
    return (bool)(mouseBuffer & button);
}