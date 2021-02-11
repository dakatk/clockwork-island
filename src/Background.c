#include "Background.h"
#include "Viewport.h"
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

	background->dest0.w = VIEWPORT_WIDTH;
	background->dest0.h = VIEWPORT_HEIGHT;
	background->dest0.x = 0;
	background->dest0.y = 0;

	background->dest1.w = VIEWPORT_WIDTH;
	background->dest1.h = VIEWPORT_HEIGHT;
	background->dest1.x = 0;
	background->dest1.y = 0;

	return true;
}

// TODO FUTURE Parallax scrolling (maybe add a third layer?)

void Background_Render(struct Background* background, SDL_Renderer* renderer)
{
	Texture_RenderRect(&background->layer0, renderer, &background->dest0);
	Texture_RenderRect(&background->layer1, renderer, &background->dest1);
}

void Background_Destroy(struct Background* background)
{
	Texture_Destroy(&background->layer0);
	Texture_Destroy(&background->layer1);
}
