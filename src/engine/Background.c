#include "engine/Background.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"

#include <stdio.h>

static struct Texture layer0;
static struct Texture layer1;

static float scrollX;
static float scrollY;

bool Background_Init(SDL_Renderer* renderer, const char* image0, const char* image1)
{
	if (!Texture_Init(&layer0, renderer, image0, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image0);
		return false;
	}

#define LAYER0_CLIP_WIDTH 320
#define LAYER0_CLIP_HEIGHT 240
#define LAYER0_CLIP_X 480
#define LAYER0_CLIP_Y 360

	layer0.clip.w = LAYER0_CLIP_WIDTH;
	layer0.clip.h = LAYER0_CLIP_HEIGHT;
	layer0.clip.x = LAYER0_CLIP_X;
	layer0.clip.y = LAYER0_CLIP_Y;

#undef LAYER0_CLIP_WIDTH
#undef LAYER0_CLIP_HEIGHT
#undef LAYER0_CLIP_X
#undef LAYER0_CLIP_Y

	if (!Texture_Init(&layer1, renderer, image1, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image1);
		return false;
	}

#define LAYER1_CLIP_WIDTH 534
#define LAYER1_CLIP_HEIGHT 400
#define LAYER1_CLIP_X 266
#define LAYER1_CLIP_Y 200

    layer1.clip.w = LAYER1_CLIP_WIDTH;
    layer1.clip.h = LAYER1_CLIP_HEIGHT;
    layer1.clip.x = LAYER1_CLIP_X;
    layer1.clip.y = LAYER1_CLIP_Y;

#undef LAYER1_CLIP_WIDTH
#undef LAYER1_CLIP_HEIGHT
#undef LAYER1_CLIP_X
#undef LAYER1_CLIP_Y

	return true;
}

void Background_Scroll()
{
    // Move clips to scrollX, scrollY
}

void Background_Render()
{
    Buffer_RenderTextureFull(&layer0);
    Buffer_RenderTextureFull(&layer1);
}

void Background_Destroy()
{
	Texture_Destroy(&layer0);
	Texture_Destroy(&layer1);
}
