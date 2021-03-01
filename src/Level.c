#include "Level.h"
#include "Bounds.h"
#include "Viewport.h"

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
    /*
	struct Bounds playerBounds = Player_GetBounds(player);
	struct RayHit minHit = {
		.intersectAt = INTER_AT_NONE,
		.intersectFrom = INTER_FROM_NONE,
		.intersectX = -1.0f,
		.intersectY = -1.0f,
		.delta = -1.0f
	};
	// TODO Only loop over platforms in the visible pool. Adjust the visible pool as the player moves
	// Possible solution:
	// 1. Player moves based on vx, vy, collision
	// 2. Viewport snaps to player, constrained to scene boundaries
	// 3. Loop over all platforms in level, if they are not offscreen then add them to the localized pool
	// The localized pool would thn be looped over when checking player physics. Since physics are checked every frame
	// (not just when the player moves), this will help reduce the load for non-action sequences
	for (struct PlatformNode* current = level->platforms; current != NULL; current = current->next)
	{
		struct Platform* platform = current->platform;

		// Temporary solution:
		if (Platform_IsOffscreen(platform) || !(platform->visible[player->currFilter]))
			continue;

		struct Bounds platformBounds = Platform_GetBounds(platform);
		struct RayHit hit = Bounds_Intersect(&playerBounds, &platformBounds, player->vx, player->vy);

		if (hit.intersectAt == INTER_AT_NONE || hit.intersectFrom == INTER_FROM_NONE)
			continue;

		if (hit.delta < minHit.delta)
			minHit = hit;
	}

	if (minHit.intersectAt == INTER_AT_NONE || minHit.intersectFrom == INTER_FROM_NONE) 
	{
		player->x += player->vx;
		player->y += player->vy;
		return;
	}

	if (minHit.intersectAt == INTER_AT_TOP)
	{
		player->onGround = true;
		player->vy = 0.0f;
	}

	if (minHit.intersectAt == INTER_AT_BOTTOM)
	{
		player->isJumping = false;
		player->vy = 0.0f;
	}

	switch (minHit.intersectFrom)
	{
		case INTER_FROM_TOP_LEFT:
			movePlayerTopLeft(player, minHit.intersectX, minHit.intersectY);
			break;

		case INTER_FROM_TOP_RIGHT:
			movePlayerTopRight(player, minHit.intersectX, minHit.intersectY);
			break;

		case INTER_FROM_BOTTOM_LEFT:
			movePlayerBottomLeft(player, minHit.intersectX, minHit.intersectY);
			break;

		case INTER_FROM_BOTTOM_RIGHT:
			movePlayerBottomRight(player, minHit.intersectX, minHit.intersectY);
			break;

		default:
			break;
	}

#define MAX_SPEED_Y 5.0f
#define MIN_SPEED_Y -5.0f
#define GRAVITY 1.0f

	if (!player->onGround)
		player->vy -= GRAVITY;

	if (player->vy > MAX_SPEED_Y)
		player->vy = MAX_SPEED_Y;

	else if (player->vy < MIN_SPEED_Y)
		player->vy = MIN_SPEED_Y;

#undef MAX_SPEED_Y
#undef MIN_SPEED_Y
#undef GRAVITY*/
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
