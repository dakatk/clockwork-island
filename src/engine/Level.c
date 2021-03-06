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
	memcpy(node->platform, platform, sizeof(struct Platform));

	node->next = level->platforms;
	level->platforms = node;
}

void Level_CheckPhysics(struct Level* level, struct Player* player)
{
    player->x += player->vx;
    player->cx += player->vx;

    for (struct PlatformNode* current = level->platforms; current != NULL; current = current->next) {

        struct Platform *platform = current->platform;

        if (Platform_IsOffscreen(platform) || !(platform->visible[player->activeFilter]))
            continue;

        // TODO implement...
    }
}

void Level_Render(struct Level* level, unsigned activeFilter)
{
	int count = 0;

	for (struct PlatformNode* current = level->platforms; current != NULL; current = current->next)
	{
	    count ++;
		struct Platform* platform = current->platform;

		if (Platform_IsOffscreen(platform) || !(platform->visible[activeFilter]))
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
