#ifndef CLOCKWORKISLAND_PLAYER_H__
#define CLOCKWORKISLAND_PLAYER_H__

#include "Direction.h"
#include "Bitmap.h"
#include "Physics.h"
#include "Filter.h"

#define PLAYER_MOVE_SPEED 3.25f
#define PLAYER_JUMP_SPEED 4.0f

#define PLAYER_WIDTH 100
#define PLAYER_HEIGHT 100

#define PLAYER_SPRITE_CLIP_SIZE 100
#define PLAYER_NUM_FILTERS 6

struct Player {
	const struct Direction* direction;
	struct Bitmap* texture;

	bool isJumping;
	bool onGround;
	int currFilter;

	float vx, vy;
	float cx, cy;
	float x, y;
	int w, h;
};

void Player_Init(struct Player* player, struct Bitmap* spritesheet, int x, int y, int w, int h);
void Player_UpdateDirection(struct Player* player);
void Player_Animate(struct Player* player);
void Player_Render(struct Player* player);
void Player_Destroy(struct Player* player);

#endif /* CLOCKWORKISLAND_PLAYER_H__ */
