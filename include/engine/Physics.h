#ifndef CLOCKWORKISLAND_PHYSICS_H__
#define CLOCKWORKISLAND_PHYSICS_H__

#include "engine/Player.h"
#include "engine/Platform.h"

void Physics_Collide(struct Player* player, struct Platform* platform, float playerOldX, float playerOldY);

#endif /* CLOCKWORKISLAND_PHYSICS_H__ */
