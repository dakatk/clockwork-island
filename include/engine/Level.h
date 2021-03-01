#ifndef CLOCKWORKISLAND_LEVEL_H__
#define CLOCKWORKISLAND_LEVEL_H__

#include "Player.h"
#include "Platform.h"
#include "Background.h"

struct PlatformNode {
	struct Platform* platform;
	struct PlatformNode* next;
};

struct Level {
	struct Background background;
	struct PlatformNode* platforms;

	bool exited;
};

void Level_Init(struct Level* level);
void Level_AddPlatform(struct Level* level, struct Platform* platform);

void Level_CheckPhysics(struct Level* level, struct Player* player);

void Level_Render(struct Level* level, unsigned currFilter);
void Level_Destroy(struct Level* level);

#endif /* CLOCKWORKISLAND_LEVEL_H__ */
