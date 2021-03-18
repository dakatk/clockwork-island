#include "engine/Background.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"

#include <stdio.h>

struct Layer {
    struct Texture texture;
    int maxScrollX;
    int maxScrollY;
};

static struct Layer layer0;
static struct Layer layer1;

bool Background_Init(SDL_Renderer* renderer, const char* image0, const char* image1)
{
    int texWidth, texHeight;

    // Layer 0
	if (!Texture_Init(&layer0.texture, renderer, image0, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image0);
		return false;
	}
	SDL_QueryTexture(layer0.texture.bitmap, NULL, NULL, &texWidth, &texHeight);

#define LAYER0_CLIP_WIDTH 700
#define LAYER0_CLIP_HEIGHT 500

	layer0.texture.clip.w = LAYER0_CLIP_WIDTH;
	layer0.texture.clip.h = LAYER0_CLIP_HEIGHT;

	layer0.maxScrollX = texWidth - LAYER0_CLIP_WIDTH;

#undef LAYER0_CLIP_WIDTH
#undef LAYER0_CLIP_HEIGHT

	// Layer 1
	if (!Texture_Init(&layer1.texture, renderer, image1, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image1);
		return false;
	}
    SDL_QueryTexture(layer1.texture.bitmap, NULL, NULL, &texWidth, &texHeight);

#define LAYER1_CLIP_WIDTH 600
#define LAYER1_CLIP_HEIGHT 400

    layer1.texture.clip.w = LAYER1_CLIP_WIDTH;
    layer1.texture.clip.h = LAYER1_CLIP_HEIGHT;

    layer1.maxScrollX = texWidth - LAYER1_CLIP_WIDTH;

#undef LAYER1_CLIP_WIDTH
#undef LAYER1_CLIP_HEIGHT

	return true;
}

void Background_Scroll()
{
    layer0.texture.clip.x = (Viewport_X * layer0.maxScrollX) / VIEWPORT_MAX_X;
    layer1.texture.clip.x = (Viewport_X * layer1.maxScrollX) / VIEWPORT_MAX_X;
}

void Background_Render()
{
    Buffer_RenderTextureFull(&layer0.texture);
    Buffer_RenderTextureFull(&layer1.texture);
}

void Background_Destroy()
{
	Texture_Destroy(&layer0.texture);
	Texture_Destroy(&layer1.texture);
}