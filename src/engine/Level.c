#include "engine/Level.h"
#include "engine/Physics.h"
#include "engine/Viewport.h"

#include <stdlib.h>
#include <string.h>

void Level_Init(struct Level* level)
{
	level->platforms = NULL;
	level->exited = false;
}

void Level_AddPlatform(struct Level* level, struct Platform* platform)
{
	struct PlatformNode* node = malloc(sizeof(struct PlatformNode));

	node->platform = malloc(sizeof(struct Platform));
	node->next = NULL;

	memcpy(node->platform, platform, sizeof(struct Platform));

	if (level->platforms == NULL) 
		level->platforms = node;
	else 
		level->platforms->next = node;
}

static inline void movePlayerTopLeft(struct Player* player, float x, float y)
{
	player->x = x;
	player->y = y;
}

static inline void movePlayerTopRight(struct Player* player, float x, float y)
{
	player->x = x - (float)player->w;
	player->y = y;
}

static inline void movePlayerBottomLeft(struct Player* player, float x, float y)
{
	player->x = x;
	player->y = y - (float)player->h;
}

static inline void movePlayerBottomRight(struct Player* player, float x, float y)
{
	player->x = x - (float)player->w;
	player->y = y - (float)player->h;
}

void Level_CheckPhysics(struct Level* level, struct Player* player)
{
    player->x += player->vx;
    player->cx += player->vx;
    // TODO implement...
}

void Level_Render(struct Level* level, unsigned currFilter)
{
	Background_Render(&level->background);

	for (struct PlatformNode* current = level->platforms; current != NULL; current = current->next)
	{
		struct Platform* platform = current->platform;

		if (Platform_IsOffscreen(platform) || !(platform->visible[currFilter]))
			continue;

		Platform_Render(platform);
	}
}

void Level_Destroy(struct Level* level)
{
	struct PlatformNode* current = level->platforms;

	while (current != NULL)
	{
		struct PlatformNode* next = current->next;

        free(current->platform);
		free(current);

		current = next;
	} 
}
