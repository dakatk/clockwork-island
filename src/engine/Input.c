#include "engine/Input.h"

#include <SDL.h>

static uint16_t keysBuffer = 0;
static uint16_t prevKeysBuffer = 0;

static uint8_t mouseBuffer = 0;

int Input_MouseX;
int Input_MouseY;

void Input_Capture()
{
	prevKeysBuffer = keysBuffer;

    SDL_Event e;
	while (SDL_PollEvent(&e))
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
                case SDLK_LEFT:
                    keysBuffer |= KEY_LEFT;
                    break;

                case SDLK_RIGHT:
                    keysBuffer |= KEY_RIGHT;
                    break;

                case SDLK_z:
                    keysBuffer |= KEY_Z;
                    break;

                case SDLK_a:
                    keysBuffer |= KEY_A;
                    break;

                case SDLK_s:
                    keysBuffer |= KEY_S;
                    break;

                case SDLK_F1:
                    keysBuffer |= KEY_F1;
                    break;

                case SDLK_0:
			    case SDLK_1:
			    case SDLK_2:
			    case SDLK_3:
			    case SDLK_4:
			    case SDLK_5:
                    keysBuffer |= 1 << (e.key.keysym.sym - SDLK_0);

                default:
                    break;
			}
		}

		else if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
                case SDLK_LEFT:
                    keysBuffer &= ~KEY_LEFT;
                    break;

                case SDLK_RIGHT:
                    keysBuffer &= ~KEY_RIGHT;
                    break;

                case SDLK_z:
                    keysBuffer &= ~KEY_Z;
                    break;

                case SDLK_a:
                    keysBuffer &= ~KEY_A;
                    break;

                case SDLK_s:
                    keysBuffer &= ~KEY_S;
                    break;

                case SDLK_F1:
                    keysBuffer &= ~KEY_F1;

                case SDLK_0:
                case SDLK_1:
                case SDLK_2:
                case SDLK_3:
                case SDLK_4:
                case SDLK_5:
                    keysBuffer &= ~(1 << (e.key.keysym.sym - SDLK_0));

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
		    Input_MouseX = e.motion.x;
		    Input_MouseY = e.motion.y;
        }
	}
}

#define KEY_BUFFER_SIZE 16

bool Input_KeyPressed(int key)
{
    if (key < 0 || key >= KEY_BUFFER_SIZE) 
        return false;

    return (keysBuffer >> key) & 1;
}

bool Input_KeyTyped(int key)
{
    if (key < 0 || key >= KEY_BUFFER_SIZE)
        return false;

	bool keyPressed = (keysBuffer >> key) & 1;
	bool prevKeyPressed = (prevKeysBuffer >> key) & 1;
    
    return keyPressed && !prevKeyPressed;
}

#undef KEY_BUFFER_SIZE

uint16_t Input_KeysBuffer()
{
    return keysBuffer;
}

#define MOUSE_BUFFER_SIZE 8

bool Input_ButtonPressed(int button)
{
    if (button < 0 || button >= MOUSE_BUFFER_SIZE)
        return false;

    return (mouseBuffer >> button) & 1;
}

#undef MOUSE_BUFFER_SIZE