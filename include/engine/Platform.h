#ifndef CLOCKWORKISLAND_PLATFORM_H__
#define CLOCKWORKISLAND_PLATFORM_H__

#include "BoundingBox.h"
#include "Texture.h"

#include <stdbool.h>
#include <stdint.h>

struct Platform {

	struct Texture* texture;
	struct BoundingBox boundingBox;

	// Encoding = Orange | Violet | Green | Blue | Red
	uint8_t visible;
	// Encoding = Left | Bottom | Right | Top
    uint8_t sides;

	double angle;
	int spriteClipX;
	int spriteClipY;

	int x, y;
	int w, h;
};

// Long boi:
void Platform_Init(struct Platform* platform, struct Texture* texture, double angle, int spriteIndex, uint8_t visible, uint8_t sides, int x, int y, int w, int h);
void Platform_SetBoundingBox(struct Platform* platform, float bw, float bh);
bool Platform_IsOffscreen(struct Platform* platform);
bool Platform_IsVisible(struct Platform* platform, uint8_t filterIndex);
void Platform_Render(struct Platform* platform);

#endif /* CLOCKWORKISLAND_PLATFORM_H__ */
