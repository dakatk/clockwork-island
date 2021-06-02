#ifndef CLOCKWORKISLAND_PLAYER_H__
#define CLOCKWORKISLAND_PLAYER_H__

#include "Direction.h"
#include "Texture.h"
#include "Filter.h"

#include <stdbool.h>

#define PLAYER_MOVE_SPEED 0.5f
#define PLAYER_JUMP_SPEED 8.5f

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 100

#define PLAYER_SPRITE_CLIP_SIZE 100
#define PLAYER_NUM_FILTERS 6

struct Player {
	const struct Direction* direction;
	struct Texture* texture;

	int activeFilter;
	int allowedFilters;
    bool isJumping;

	float vx, vy;
	float x, y;
	int w, h;
};

void Player_Init(struct Player* player, struct Texture* spritesheet, int x, int y, int w, int h, int u);
void Player_UpdateDirection(struct Player* player);
void Player_Animate(struct Player* player);
void Player_Render(struct Player* player);

#endif /* CLOCKWORKISLAND_PLAYER_H__ */
