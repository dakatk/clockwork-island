#ifndef CLOCKWORKISLAND_PHYSICS_H__
#define CLOCKWORKISLAND_PHYSICS_H__

#include "BoundingBox.h"
#include "Player.h"
#include "Platform.h"

bool Physics_Intersects(struct Player* player, struct Platform* platform);
void Physics_Collide(struct Player* player, struct Platform* platform, float playerOldX, float playerOldY);

#endif /* CLOCKWORKISLAND_PHYSICS_H__ */
