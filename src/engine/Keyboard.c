#include "Keyboard.h"

#include <stdint.h>
#include <SDL2/SDL.h>

#define KEY_BUFFER_SIZE 32

static uint32_t keysBuffer = 0;
static uint32_t prevKeysBuffer = 0;

void Keyboard_CaptureInput()
{
	prevKeysBuffer = keysBuffer;

#define SET_KEY(key) keysBuffer |= (1 << key)
#define UNSET_KEY(key) keysBuffer &= ~(1 << key)

    SDL_Event e;
	while (SDL_PollEvent(&e))
	{
		if (e.type == SDL_QUIT)
			SET_KEY(KEY_QUIT);

		if (e.type == SDL_KEYDOWN)
		{
			if (e.key.keysym.sym == SDLK_q &&
				e.key.keysym.mod == KMOD_LCTRL)
					SET_KEY(KEY_QUIT);

			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				SET_KEY(KEY_LEFT);
				break;

			case SDLK_RIGHT:
				SET_KEY(KEY_RIGHT);
				break;

			case SDLK_z:
				SET_KEY(KEY_Z);
				break;

			case SDLK_a:
				SET_KEY(KEY_A);
				break;

			case SDLK_s:
				SET_KEY(KEY_S);
				break;

			case SDLK_F1:
				SET_KEY(KEY_F1);
				break;

			default:
				break;
			}
		}

		if (e.type == SDL_KEYUP)
		{
			switch (e.key.keysym.sym)
			{
			case SDLK_LEFT:
				UNSET_KEY(KEY_LEFT);
				break;

			case SDLK_RIGHT:
				UNSET_KEY(KEY_RIGHT);
				break;

			case SDLK_z:
				UNSET_KEY(KEY_Z);
				break;

			case SDLK_a:
				UNSET_KEY(KEY_A);
				break;

			case SDLK_s:
				UNSET_KEY(KEY_S);
                break;

            case SDLK_F1:
                UNSET_KEY(KEY_F1);

			default:
				break;
			}
		}
	}
#undef SET_KEY
#undef UNSET_KEY
}

bool Keyboard_KeyPressed(int key)
{
    if (key < 0 || key >= KEY_BUFFER_SIZE) 
        return false;

    return (keysBuffer >> key) & 1;
}

bool Keyboard_KeyTyped(int key)
{
    if (key < 0 || key >= KEY_BUFFER_SIZE)
        return false;

	bool keyPressed = (keysBuffer >> key) & 1;
	bool prevKeyPressed = (prevKeysBuffer >> key) & 1;
    
    return keyPressed && !prevKeyPressed;
}
#undef KEY_BUFFER_SIZE