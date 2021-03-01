#include "engine/Bitmap.h"

// #include <SDL2/SDL.h>
// #include <SDL2/SDL_image.h>
#include <stdlib.h>
#include <string.h>

void Bitmap_Init(struct Bitmap* bitmap, unsigned char* pixels, size_t pixelsSize, int clipSize)
{
    bitmap->pixels = malloc(pixelsSize);
    memcpy(bitmap->pixels, pixels, pixelsSize);

    bitmap->clipX = 0;
    bitmap->clipY = 0;
    bitmap->clipSize = clipSize;
	/*SDL_Surface* image = IMG_Load(filename);
	if (image == NULL)
		return false;

    bitmap->bitmap = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);

    bitmap->clip.x = 0;
    bitmap->clip.y = 0;
    bitmap->clip.w = clipSize;
    bitmap->clip.h = clipSize;

	return true;*/
}

void Bitmap_MoveClip(struct Bitmap* bitmap, int clipX, int clipY)
{
    bitmap->clipX = clipX * bitmap->clipSize;
    bitmap->clipY = clipY * bitmap->clipSize;
	/*bitmap->clip.x = clipX * bitmap->clip.h;
	bitmap->clip.y = clipY * bitmap->clip.w;*/
}

void Bitmap_Destroy(struct Bitmap* texture)
{
	free(texture->pixels);
}
