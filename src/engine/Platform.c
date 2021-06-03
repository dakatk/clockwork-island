#include "engine/Platform.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"

void Platform_Init(struct Platform* platform, struct Texture* texture, double angle, int spriteIndex, uint8_t visible, uint8_t sides, int x, int y, int w, int h)
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

	platform->visible = visible;
	platform->sides = sides;
	platform->angle = angle;
	platform->x = x;
	platform->y = y;
	platform->h = h;
	platform->w = w;
}

void Platform_SetBoundingBox(struct Platform* platform, float bw, float bh)
{
    platform->boundingBox.halfWidth = bw / 2.0f;
    platform->boundingBox.halfHeight = bh / 2.0f;

    platform->boundingBox.cx = (float)platform->x + ((float)platform->w / 2.0f);
    platform->boundingBox.cy = (float)platform->y - ((float)platform->h / 2.0f);
}

bool Platform_IsOffscreen(struct Platform* platform)
{
    bool offscreenLeft = platform->x > Viewport_X + Buffer_Width;
    bool offscreenRight = platform->x + platform->w < Viewport_X;
    bool offscreenAbove = platform->y + platform->h > Viewport_Y + Buffer_Height;
    bool offscreenBelow = platform->y < Viewport_Y;

	return offscreenLeft || offscreenRight || offscreenAbove || offscreenBelow;
}

bool Platform_IsVisible(struct Platform* platform, uint8_t filterIndex)
{
    if (filterIndex >= NUM_FILTERS)
        return true;

    return (platform->visible >> filterIndex) & 0x1;
}

void Platform_Render(struct Platform* platform)
{
	Texture_MoveClip(platform->texture, platform->spriteClipX, platform->spriteClipY);

	int actualX = platform->x - Viewport_X;
	int actualY = Buffer_Height - platform->y + Viewport_Y;

	Buffer_RenderTextureRotated(platform->texture, platform->angle, actualX, actualY, platform->w, platform->h);
}
