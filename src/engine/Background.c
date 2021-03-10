#include "engine/Background.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"

#include <stdio.h>

static struct Texture layer0;
static struct Texture layer1;

static float scrollX;
static float scrollY;

// Pixels per movement
const float ppm;

bool Background_Init(SDL_Renderer* renderer, const char* image0, const char* image1)
{
	if (!Texture_Init(&layer0, renderer, image0, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image0);
		return false;
	}

	if (!Texture_Init(&layer1, renderer, image1, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image1);
		return false;
	}
	return true;
}

void Background_Scroll()
{

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
