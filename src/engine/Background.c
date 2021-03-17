#include "engine/Background.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"

#include <stdio.h>

static struct Texture layer0;
static struct Texture layer1;

static int maxScrollX0;
static int maxScrollX1;

bool Background_Init(SDL_Renderer* renderer, const char* image0, const char* image1)
{
    int texWidth, texHeight;

    // Layer 0
	if (!Texture_Init(&layer0, renderer, image0, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image0);
		return false;
	}
	SDL_QueryTexture(layer0.bitmap, NULL, NULL, &texWidth, &texHeight);

#define LAYER0_CLIP_WIDTH 700
#define LAYER0_CLIP_HEIGHT 500

	layer0.clip.w = LAYER0_CLIP_WIDTH;
	layer0.clip.h = LAYER0_CLIP_HEIGHT;

	maxScrollX0 = texWidth - LAYER0_CLIP_WIDTH;

#undef LAYER0_CLIP_WIDTH
#undef LAYER0_CLIP_HEIGHT

	// Layer 1
	if (!Texture_Init(&layer1, renderer, image1, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image1);
		return false;
	}
    SDL_QueryTexture(layer0.bitmap, NULL, NULL, &texWidth, &texHeight);

#define LAYER1_CLIP_WIDTH 600
#define LAYER1_CLIP_HEIGHT 400

    layer1.clip.w = LAYER1_CLIP_WIDTH;
    layer1.clip.h = LAYER1_CLIP_HEIGHT;

    maxScrollX1 = texWidth - LAYER1_CLIP_WIDTH;

#undef LAYER1_CLIP_WIDTH
#undef LAYER1_CLIP_HEIGHT

	return true;
}

void Background_Scroll()
{
    layer0.clip.x = (Viewport_X * maxScrollX0) / VIEWPORT_MAX_X;
    layer1.clip.x = (Viewport_X * maxScrollX1) / VIEWPORT_MAX_X;
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