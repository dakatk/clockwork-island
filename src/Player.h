#ifndef GAME_PLAYER_H__
#define GAME_PLAYER_H__

#include "Direction.h"
#include "Texture.h"
#include "Bounds.h"
#include "Filter.h"

#define PLAYER_MOVE_SPEED 3.25f
#define PLAYER_JUMP_SPEED 4.0f
#define PLAYER_HEALTH 50

#define PLAYER_WIDTH 75
#define PLAYER_HEIGHT 75

#define PLAYER_SPRITE_CLIP_SIZE 100
#define PLAYER_NUM_FILTERS 6

struct Player {
	const struct Direction* direction;
	struct Texture* texture;

	bool isJumping;
	bool onGround;
	int currFilter;
	int health;

	float vx, vy;
	float x, y;
	int w, h;
};

void Player_Init(struct Player* player, struct Texture* spritesheet, int x, int y, int w, int h);

struct Bounds Player_GetBounds(struct Player* player);

void Player_UpdateDirection(struct Player* player);
void Player_Animate(struct Player* player);
void Player_Render(struct Player* player, SDL_Renderer* renderer);

#endif /* GAME_PLAYER_H__ */
