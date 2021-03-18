#include "engine/Texture.h"

#include <SDL.h>
#include <SDL_image.h>

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

void Texture_MoveClip(struct Texture* texture, int col, int row)
{
	texture->clip.x = col * texture->clip.h;
	texture->clip.y = row * texture->clip.w;
}

void Texture_Destroy(struct Texture* texture)
{
	SDL_DestroyTexture(texture->bitmap);
}
