#ifndef CLOCKWORKISLAND_PLATFORM_H__
#define CLOCKWORKISLAND_PLATFORM_H__

#include "Bitmap.h"
#include "Physics.h"

#define PLATFORM_SPRITE_CLIP_SIZE 128
#define NUM_PLATFORM_VISIBLE_OPTIONS 6

struct Platform {

	struct Bitmap* bitmap;
	bool visible[NUM_PLATFORM_VISIBLE_OPTIONS];

	int spriteClipX;
	int spriteClipY;
	int flipped;

	int x, y;
	int w, h;
};

// Long boi:
void Platform_Init(struct Platform* platform, struct Bitmap* texture, int flipped, int spriteIndex, int x, int y, int w, int h);

bool Platform_IsOffscreen(struct Platform* platform);

void Platform_Render(struct Platform* platform);

#endif /* CLOCKWORKISLAND_PLATFORM_H__ */
