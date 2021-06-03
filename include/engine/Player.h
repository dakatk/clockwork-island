#ifndef CLOCKWORKISLAND_PLAYER_H__
#define CLOCKWORKISLAND_PLAYER_H__

#include "BoundingBox.h"
#include "Direction.h"
#include "Texture.h"
#include "Filter.h"

#include <stdbool.h>

struct Player {
	const struct Direction* direction;
	struct Texture* texture;
	struct BoundingBox boundingBox;

	int activeFilter;
	int allowedFilters;
    bool isJumping;

	float vx, vy;
	float x, y;
	float oldCX, oldCY;
	int w, h;
};

void Player_Init(struct Player* player, struct Texture* spritesheet, int x, int y, int w, int h, int u);
void Player_SetBoundingBox(struct Player* player, float bw, float bh);
void Player_UpdateDirection(struct Player* player);
void Player_Animate(struct Player* player);
void Player_Render(struct Player* player);

#endif /* CLOCKWORKISLAND_PLAYER_H__ */
