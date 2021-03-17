#include "engine/Background.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"

#include <stdio.h>

#define LAYER0_CLIP_WIDTH 534
#define LAYER0_CLIP_HEIGHT 400
#define LAYER0_CLIP_X 266
#define LAYER0_CLIP_Y 200

#define LAYER1_CLIP_WIDTH 320
#define LAYER1_CLIP_HEIGHT 240
#define LAYER1_CLIP_X 480
#define LAYER1_CLIP_Y 360

static struct Texture layer0;
static struct Texture layer1;

static int width0;
static int height0;
static int width1;
static int height1;

bool Background_Init(SDL_Renderer* renderer, const char* image0, const char* image1)
{
	if (!Texture_Init(&layer0, renderer, image0, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image0);
		return false;
	}
	SDL_QueryTexture(layer0.bitmap, NULL, NULL, &width0, &height0);

	layer0.clip.w = LAYER0_CLIP_WIDTH;
	layer0.clip.h = LAYER0_CLIP_HEIGHT;
	layer0.clip.x = LAYER0_CLIP_X;
	layer0.clip.y = LAYER0_CLIP_Y;

	if (!Texture_Init(&layer1, renderer, image1, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image1);
		return false;
	}
    SDL_QueryTexture(layer0.bitmap, NULL, NULL, &width1, &height1);

    layer1.clip.w = LAYER1_CLIP_WIDTH;
    layer1.clip.h = LAYER1_CLIP_HEIGHT;
    layer1.clip.x = LAYER1_CLIP_X;
    layer1.clip.y = LAYER1_CLIP_Y;

	return true;
}

void Background_Scroll()
{
    int maxScrollX = width0 - LAYER0_CLIP_WIDTH;
    float scrollX = ((float)Viewport_X / VIEWPORT_MAX_X) * (float)maxScrollX;

    layer0.clip.x = (int)scrollX;
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

#undef LAYER0_CLIP_WIDTH
#undef LAYER0_CLIP_HEIGHT
#undef LAYER0_CLIP_X
#undef LAYER0_CLIP_Y

#undef LAYER1_CLIP_WIDTH
#undef LAYER1_CLIP_HEIGHT
#undef LAYER1_CLIP_X
#undef LAYER1_CLIP_Y