#include "engine/Background.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"

#include <stdio.h>

bool Background_Init(struct Background* background, SDL_Renderer* renderer, const char* image0, const char* image1)
{
	if (!Texture_Init(&background->layer0, renderer, image0, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image0);
		return false;
	}

	if (!Texture_Init(&background->layer1, renderer, image1, FULL_IMAGE))
	{
		fprintf(stderr, "Failed to load image '%s'.\n", image1);
		return false;
	}
	return true;
}

void Background_Scroll(struct Background* background)
{

}

void Background_Render(struct Background* background)
{
    Buffer_RenderTextureFull(&background->layer0);
    Buffer_RenderTextureFull(&background->layer1);
}

void Background_Destroy(struct Background* background)
{
	Texture_Destroy(&background->layer0);
	Texture_Destroy(&background->layer1);
}
