#ifndef CLOCKWORKISLAND_TEXTURE_H__
#define CLOCKWORKISLAND_TEXTURE_H__

#include <SDL2/SDL.h>
#include "Bool.h"

#define FULL_IMAGE -1

struct Bitmap {
    unsigned char* pixels;

    int clipX, clipY;
    int clipSize;
	/*SDL_Texture* bitmap;
	SDL_Rect clip;*/
};

// bool Texture_Init(struct Bitmap* bitmap, SDL_Renderer* renderer, const char* filename, int clipSize);
void Bitmap_Init(struct Bitmap* bitmap, unsigned char* pixels, size_t pixelsSize, int clipSize);

void Bitmap_MoveClip(struct Bitmap* bitmap, int clipX, int clipY);

void Bitmap_Destroy(struct Bitmap* texture);

#endif /* CLOCKWORKISLAND_TEXTURE_H__ */
