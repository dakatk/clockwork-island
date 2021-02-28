#ifndef CLOCKWORKISLAND_TEXTURE_H__
#define CLOCKWORKISLAND_TEXTURE_H__

#include <SDL2/SDL.h>
#include "Bool.h"

#define FULL_IMAGE -1

struct Texture {
	SDL_Texture* bitmap;
	SDL_Rect clip;
};

bool Texture_Init(struct Texture* texture, SDL_Renderer* renderer, const char* filename, int clipSize);

void Texture_MoveClip(struct Texture* texture, int clipX, int clipY);

void Texture_Destroy(struct Texture* texture);

#endif /* CLOCKWORKISLAND_TEXTURE_H__ */
