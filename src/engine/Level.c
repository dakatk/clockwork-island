#include "engine/Level.h"
#include "engine/Physics.h"

#include <stdlib.h>
#include <string.h>

void Level_Init(struct Level* level)
{
	level->platforms = NULL;
}

void Level_AddPlatform(struct Level* level, struct Platform* platform)
{
	struct PlatformNode* node = malloc(sizeof(struct PlatformNode));

	node->platform = malloc(sizeof(struct Platform));
	memcpy(node->platform, platform, sizeof(struct Platform));

	node->next = level->platforms;
	level->platforms = node;
}

void Level_CheckPhysics(struct Level* level, struct Player* player)
{
/*    float playerOldX = player->x;
    float playerOldY = player->y;

#define GRAVITY 0.2f
#define FRICTION 0.8f

    player->vy -= GRAVITY;

    player->vy = fmaxf(fminf(player->vy, PLAYER_MAX_JUMP_SPEED), -PLAYER_MAX_JUMP_SPEED);
    player->vx = fmaxf(fminf(player->vx, PLAYER_MAX_MOVE_SPEED), -PLAYER_MAX_MOVE_SPEED);

    player->x += player->vx;
    player->y += player->vy;

    player->vx *= FRICTION;

    if (fabsf(player->vx) <= 0.05f)
        player->vx = 0.0f;

#undef GRAVITY
#undef FRICTION*/

    for (struct PlatformNode* current = level->platforms; current != NULL; current = current->next) {

        struct Platform *platform = current->platform;

        if (Platform_IsOffscreen(platform) || !Platform_IsVisible(platform, player->activeFilter))
            continue;

        if (Physics_Intersects(player, platform))
            Physics_Collide(player, platform);
    }
}

void Level_Render(struct Level* level, unsigned activeFilter)
{
	int count = 0;

	for (struct PlatformNode* current = level->platforms; current != NULL; current = current->next)
	{
	    count ++;
		struct Platform* platform = current->platform;

		if (Platform_IsOffscreen(platform) || !Platform_IsVisible(platform, activeFilter))
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
