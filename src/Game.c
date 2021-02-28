/*
 *  Game.c
 *  Clockwork Island
 *
 *  Created by Dusten Knull on 02/05/21.
 *  Copyright © 2021 Dusten Knull. All rights reserved.
 */

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include <stdio.h>

#include "Keyboard.h"
#include "LevelLoader.h"
#include "Viewport.h"
#include "Buffer.h"

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
	printf("Running as executable '%s'\n", argv[0]);

#define GAME_TITLE "Clockwork Island (Alpha v0.0.1)"

	if (!SDL2_InitAll(GAME_TITLE, IMG_INIT_PNG))
	{
		fprintf(stderr, "SDL2 failed to initialize with error: %s", SDL_GetError());
		return Cleanup(1);
	}
#undef GAME_TITLE

	if (!LevelLoader_LoadResources(&level, renderer))
	{
		fprintf(stderr, "Failed to load game textures!\n");
		return Cleanup(1);
	}

	if (!LoadLevel(0)) 
		return Cleanup(1);

	do {
		Keyboard_CaptureInput();

		if (Keyboard_KeyPressed(KEY_QUIT))
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
	char levelFile[30];
	snprintf(levelFile, 30, "resources/levels/level%d.lvl", levelNum);

	if (!LevelLoader_LoadLevelFile(&level, &player, levelFile))
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
	if (Keyboard_KeyTyped(KEY_A)) 
	{
		player.currFilter --;

		if (player.currFilter < 0)
			player.currFilter = PLAYER_NUM_FILTERS - 1;
	}
	else if (Keyboard_KeyTyped(KEY_S)) 
	{
		player.currFilter ++;

		if (player.currFilter >= PLAYER_NUM_FILTERS)
			player.currFilter = 0;
	}
}

void UpdateLoop()
{
	if (Keyboard_KeyTyped(KEY_F1))
		ToggleFullscreen();

	UpdatePlayerFilter();

	if (Keyboard_KeyPressed(KEY_LEFT))
		player.vx = -PLAYER_MOVE_SPEED;

	else if (Keyboard_KeyPressed(KEY_RIGHT))
		player.vx = PLAYER_MOVE_SPEED;

	else player.vx = 0.0f;

	if (Keyboard_KeyPressed(KEY_Z)) 
		player.vy = -PLAYER_JUMP_SPEED;

	Level_CheckPhysics(&level, &player);

	Viewport_SnapTo(player.cx, player.cy);
	Viewport_Constrain();

	Player_UpdateDirection(&player);
	Player_Animate(&player);
}

void RenderLoop()
{
	Buffer_Begin();

	Level_Render(&level, player.currFilter);
	Player_Render(&player);

	Buffer_Present();
}

int Cleanup(int statusCode)
{
	LevelLoader_UnloadResources(&level);
	Level_Destroy(&level);
	Player_Destroy(&player);
	Buffer_Destroy();

	SDL_ClearHints();
	SDL_DestroyWindow(window);

	IMG_Quit();
	SDL_Quit();

	return statusCode;
}
