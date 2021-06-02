/*
 *  Clockwork Island
 *
 *  Created by Dusten Knull on 02/05/21.
 *  Copyright © 2021 Dusten Knull. All rights reserved.
 */

#include <SDL.h>
#include <SDL_image.h>

#include <stdio.h>

#include "engine/Input.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"
#include "engine/Background.h"

#include "AssetLoader.h"

SDL_Window* window;
SDL_Renderer* renderer;

struct Player player;
struct Level level;

bool SDL2_InitAll(const char* title, int imgFlags);

void UpdateLoop();
void RenderLoop();

bool LoadLevel(int levelNum);
int Cleanup(int);

int main(int argc, char* argv[])
{
    if (argc > 1)
    {
        fprintf(stderr, "'%s' does not take any arguments.\n", argv[0]);
        return -1;
    }
	printf("Running from executable '%s'\n", argv[0]);

#define GAME_TITLE "Clockwork Island (Alpha v0.0.1)"

	if (!SDL2_InitAll(GAME_TITLE, IMG_INIT_PNG))
	{
		fprintf(stderr, "SDL2 failed to initialize with error: %s", SDL_GetError());
		return Cleanup(1);
	}

#undef GAME_TITLE

	if (!AssetLoader_LoadResources(renderer))
	{
		fprintf(stderr, "Failed to load game textures!\n");
		return Cleanup(1);
	}

	if (!LoadLevel(0)) 
		return Cleanup(1);

	do {
        Input_Capture();

		if (Input_KeyPressed(KEY_QUIT))
		    break;

		UpdateLoop();
		RenderLoop();

	} while (true);

	return Cleanup(0);
}

bool SDL2_InitAll(const char* title, int imgFlags)
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return false;

	window = SDL_CreateWindow(title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
							BUFFER_WIDTH, BUFFER_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL)
		return false;

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (renderer == NULL)
		return false;

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

	SDL_RaiseWindow(window);

	if (!(IMG_Init(imgFlags) & imgFlags))
		return false;

	SDL_RenderClear(renderer);

	Buffer_Init(renderer);

	return true;
}

bool LoadLevel(int levelNum)
{
#define LEVEL_FILE_REL_PATH "resources/levels/level%d.bin"

	char levelFile[30];
	snprintf(levelFile, 30, LEVEL_FILE_REL_PATH, levelNum);

#undef LEVEL_FILE_REL_PATH

	if (!AssetLoader_LoadLevelFile(&level, &player, levelFile))
	{
		fprintf(stderr, "Error: Failed to load level data!\n");
		return false;
	}
	return true;
}

void ToggleFullscreen()
{
    bool isFullscreen = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
}

static inline void UpdatePlayerFilter()
{
	if (Input_KeyTyped(KEY_A))
	{
		player.activeFilter --;

		if (player.activeFilter < 0)
			player.activeFilter = player.allowedFilters;
	}
	else if (Input_KeyTyped(KEY_S))
	{
		player.activeFilter ++;

		if (player.activeFilter > player.allowedFilters)
			player.activeFilter = 0;
	}
	else if (Input_KeyTyped(KEY_0 | KEY_1 | KEY_2 | KEY_3 | KEY_4 | KEY_5))
    {
	    uint16_t buffer = Input_KeysBuffer();
	    for (int i = player.allowedFilters; i >= 0; i --)
        {
	        if (buffer & (1 << i))
            {
	            player.activeFilter = i;
	            break;
            }
        }
    }
}

void UpdateLoop()
{
	if (Input_KeyTyped(KEY_F1))
		ToggleFullscreen();

	UpdatePlayerFilter();

	if (Input_KeyPressed(KEY_LEFT))
		player.vx -= PLAYER_MOVE_SPEED;

	else if (Input_KeyPressed(KEY_RIGHT))
		player.vx += PLAYER_MOVE_SPEED;

	if (Input_KeyPressed(KEY_Z) && !player.isJumping)
    {
	    player.isJumping = true;
        player.vy += PLAYER_JUMP_SPEED;
    }

	Level_CheckPhysics(&level, &player);

	float playerCenterX = player.x + ((float)player.w / 2.0f);
	float playerCenterY = player.y - ((float)player.h / 2.0f);

	Viewport_SnapTo(playerCenterX, playerCenterY);
	Viewport_Constrain();

	Background_Scroll();

	Player_UpdateDirection(&player);
	Player_Animate(&player);
}

void RenderLoop()
{
	Buffer_Begin();

	Background_Render();
	Level_Render(&level, player.activeFilter);
	Player_Render(&player);

	Buffer_Present();
}

int Cleanup(int statusCode)
{
    AssetLoader_UnloadResources();
	Level_Destroy(&level);
	Buffer_Destroy();

	SDL_ClearHints();
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return statusCode;
}
