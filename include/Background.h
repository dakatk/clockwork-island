#ifndef GAME_BACKGROUND_H__
#define GAME_BACKGROUND_H__

#include <SDL2/SDL_rect.h>
#include "Texture.h"

struct Background {
	struct Texture layer0;
	struct Texture layer1;

	SDL_Rect dest0;
	SDL_Rect dest1;
};

bool Background_Init(struct Background* background, SDL_Renderer* renderer, const char* image0, const char* image1);
void Background_Render(struct Background* background, SDL_Renderer* renderer);
void Background_Destroy(struct Background* background);

#endif /* GAME_BACKGROUND_H__ */
