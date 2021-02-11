#include "Platform.h"
#include "Viewport.h"

void Platform_Init(struct Platform* platform, struct Texture* texture, double angle, int spriteIndex, int x, int y, int w, int h)
{
	platform->texture = texture;

	int spriteClipX = spriteIndex;
	int spriteClipY = 0;

#define PLATFORM_SPRITES_PER_ROW 15

	while (spriteClipX >= PLATFORM_SPRITES_PER_ROW)
	{
		spriteClipX -= PLATFORM_SPRITES_PER_ROW;
		spriteClipY ++;
	}
#undef PLATFORM_SPRITES_PER_ROW

	platform->spriteClipX = spriteClipX;
	platform->spriteClipY = spriteClipY;

	for (int i = 0; i < NUM_PLATFORM_VISIBLE_OPTIONS; i ++)
		platform->visible[i] = false;

	platform->angle = angle;
	platform->x = x;
	platform->y = y;
	platform->h = h;
	platform->w = w;
}

struct Bounds Platform_GetBounds(struct Platform* platform)
{
	struct Bounds bounds = {
		.x = (platform->x) + 1,
		.y = (platform->y) + 1,
		.w = (platform->w) - 2,
		.h = (platform->h) - 2
	};

	return bounds;
}

bool Platform_IsOffscreen(struct Platform* platform)
{
	// Platform to the left of viewport left edge
	if (platform->x > Viewport_X + VIEWPORT_WIDTH)
		return true;

	// Platform to the right of viewport right edge
	else if (platform->x + platform->w < Viewport_X)
		return true;

	// Platform above viewport top edge
	if (platform->y + platform->h > Viewport_Y + VIEWPORT_HEIGHT)
		return true;

	// Platform below viewport bottom edge
	if (platform->y < Viewport_Y)
		return true;

	return false;
}

void Platform_Render(struct Platform* platform, SDL_Renderer* renderer)
{
	Texture_MoveClip(platform->texture, platform->spriteClipX, platform->spriteClipY);

	int actualX = platform->x - Viewport_X;
	int actualY = VIEWPORT_HEIGHT - platform->y - Viewport_Y;

	Texture_RenderRotated(platform->texture, renderer, platform->angle, actualX, actualY, platform->w, platform->h);
}
