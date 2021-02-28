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

void Texture_Destroy(struct Texture* texture)
{
	SDL_DestroyTexture(texture->bitmap);
}
