#include "Background.h"
#include "Viewport.h"
#include "Buffer.h"

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

// TODO FUTURE Parallax scrolling (maybe add a third layer?)

void Background_Render(struct Background* background)
{
    Buffer_BlitBitmapFull(&background->layer0);
    Buffer_BlitBitmapFull(&background->layer1);
}

void Background_Destroy(struct Background* background)
{
    Bitmap_Destroy(&background->layer0);
    Bitmap_Destroy(&background->layer1);
}
