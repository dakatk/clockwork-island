#ifndef GAME_LEVEL_H__
#define GAME_LEVEL_H__

#include <SDL2/SDL.h>

#include "Player.h"
#include "Platform.h"
#include "Background.h"

struct Node {
	struct Platform* platform;
	struct Node* next;
};

struct Level {
	struct Background background;
	struct Node* platforms;

	bool exited;
};

void Level_Init(struct Level* level);

bool Level_SetBackground(struct Level* level, SDL_Renderer* renderer, const char* image0, const char* image1);
void Level_AddPlatform(struct Level* level, struct Platform* platform);

void Level_CheckPhysics(struct Level* level, struct Player* player);

void Level_Render(struct Level* level, SDL_Renderer* renderer, unsigned currFilter);
void Level_Destroy(struct Level* level);

#endif /* GAME_LEVEL_H__ */
