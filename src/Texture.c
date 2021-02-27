#include "Texture.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

bool Texture_Init(struct Texture* texture, SDL_Renderer* renderer, const char* filename, int clipSize)
{
	SDL_Surface* image = IMG_Load(filename);
	if (image == NULL)
		return 0;

	texture->bitmap = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

	texture->clip.x = 0;
	texture->clip.y = 0;
	texture->clip.w = clipSize;
	texture->clip.h = clipSize;

	return 1;
}

void Texture_MoveClip(struct Texture* texture, int clipX, int clipY)
{
	texture->clip.x = clipX * texture->clip.h;
	texture->clip.y = clipY * texture->clip.w;
}

void Texture_GetBitmapDims(struct Texture* texture, int* outW, int* outH)
{
	SDL_QueryTexture(texture->bitmap, NULL, NULL, outW, outH);
}

static inline bool clipFullImage(SDL_Rect clip)
{
	return clip.w == FULL_IMAGE || clip.h == FULL_IMAGE;
}

static void RenderRect(struct Texture* texture, SDL_Renderer* renderer, SDL_Rect* dest)
{
    SDL_Rect* src = NULL;

    if (!clipFullImage(texture->clip))
        src = &texture->clip;

    SDL_RenderCopy(renderer, texture->bitmap, src, dest);
}

void Texture_Render(struct Texture* texture, SDL_Renderer* renderer, int x, int y, int w, int h)
{
	SDL_Rect dest = {
		.x = x,
		.y = y,
		.w = w,
		.h = h
	};
    RenderRect(texture, renderer, &dest);
}

void Texture_RenderRotated(struct Texture* texture, SDL_Renderer* renderer,
						double angle, int x, int y, int w, int h)
{
	SDL_Rect* dest = NULL;

	if (!clipFullImage(texture->clip)) 
	{
		SDL_Rect clip = {
			.x = x,
			.y = y,
			.w = w,
			.h = h
		};
		dest = &clip;
	}
	SDL_RenderCopyEx(renderer, texture->bitmap, &texture->clip, dest, angle, NULL, SDL_FLIP_NONE);
}

void Texture_RenderFull(struct Texture* texture, SDL_Renderer* renderer)
{
    RenderRect(texture, renderer, NULL);
}

void Texture_Destroy(struct Texture* texture)
{
	SDL_DestroyTexture(texture->bitmap);
}
