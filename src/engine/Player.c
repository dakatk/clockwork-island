#include "engine/Player.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"

// NULL means no filter active
static const struct Filter* allFilters[PLAYER_NUM_FILTERS] = {
		NULL, &Filter_RED,
		&Filter_GREEN, &Filter_BLUE,
		&Filter_ORANGE, &Filter_VIOLET
};

void Player_Init(struct Player* player, struct Bitmap* spritesheet, int x, int y, int w, int h)
{
	player->direction = &Direction_STAND_RIGHT;
	player->texture = spritesheet;
	player->currFilter = 0;

	player->vx = 0.0f;
	player->vy = 0.0f;
	player->cx = (float)x + (float)w / 2.0f;
	player->cy = (float)y - (float)h / 2.0f;
	player->x = (float)x;
	player->y = (float)y;
	player->w = w;
	player->h = h;
}

struct Bounds Player_GetBounds(struct Player* player)
{
	struct Bounds bounds = {
		.x = (player->x) + 10,
		.w = (player->w) - 20,
		.y = player->y,
		.h = player->h
	};
	return bounds;
}

void Player_UpdateDirection(struct Player* player)
{
	// Right
	if (player->vx > 0.0f) 
	{
		if (player->vy != 0.0f) 
			player->direction = &Direction_JUMP_RIGHT;
		else
			player->direction = &Direction_WALK_RIGHT;
	}
	// Left
	else if (player->vx < 0.0f)
	{
		if (player->vy != 0.0f) 
			player->direction = &Direction_JUMP_LEFT;
		else
			player->direction = &Direction_WALK_LEFT;
	}
	// Neither 
	else
	{
		if (player->vy != 0.0f)
		{
			bool prevLeft = player->direction == &Direction_WALK_LEFT || player->direction == &Direction_STAND_LEFT;
			bool prevRight = player->direction == &Direction_WALK_RIGHT || player->direction == &Direction_STAND_RIGHT;

			if (prevLeft)
				player->direction = &Direction_JUMP_LEFT;

			else if (prevRight)
				player->direction = &Direction_JUMP_RIGHT;
		}
		else 
		{
			bool prevLeft = player->direction == &Direction_WALK_LEFT || player->direction == &Direction_JUMP_LEFT;
			bool prevRight = player->direction == &Direction_WALK_RIGHT || player->direction == &Direction_JUMP_RIGHT;

			if (prevLeft)
				player->direction = &Direction_STAND_LEFT;

			else if (prevRight)
				player->direction = &Direction_STAND_RIGHT;
		}
	}
}

void Player_Animate(struct Player* player)
{
	static int clipX = 0;
	static int ticks = 0;

	int frames = (player->direction)->frames;
	int waitTime = (player->direction)->sleep;
	int clipY = (player->direction)->value;

	if (ticks >= waitTime)
	{
		clipX ++;
		if (clipX >= frames)
			clipX = 0;

		ticks = 0;
	}
	else ticks ++;

	Bitmap_MoveClip(player->texture, clipX, clipY);
}

void Player_Render(struct Player* player)
{
	const struct Filter* drawFilter = allFilters[player->currFilter];

	if (drawFilter != NULL)
		Buffer_ApplyFilter(drawFilter);

	float actualX = player->x - (float)Viewport_X;
	float actualY = BUFFER_HEIGHT - player->y - (float)Viewport_Y + 1.0f;

    Buffer_BlitBitmap(player->texture, (int) actualX, (int) actualY, player->w, player->h);
}

void Player_Destroy(struct Player* player)
{
    Bitmap_Destroy(player->texture);
}
