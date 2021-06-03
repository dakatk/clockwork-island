#ifndef CLOCKWORKISLAND_PHYSICS_H__
#define CLOCKWORKISLAND_PHYSICS_H__

#include "BoundingBox.h"
#include "Player.h"
#include "Platform.h"

bool Physics_Intersects(struct BoundingBox* a, struct BoundingBox* b);
void Physics_MovePlayer(struct Player* player, float gravity, float friction, float maxJumpSpeed, float maxMoveSpeed, float minMoveSpeed);
void Physics_Collide(struct Player* player, struct Platform* platform);

#endif /* CLOCKWORKISLAND_PHYSICS_H__ */
