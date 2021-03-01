#ifndef CLOCKWORKISLAND_BACKGROUND_H__
#define CLOCKWORKISLAND_BACKGROUND_H__

#include "Bitmap.h"

struct Background {
	struct Bitmap layer0;
	struct Bitmap layer1;
};

bool Background_Init(struct Background* background, SDL_Renderer* renderer, const char* image0, const char* image1);
void Background_Render(struct Background* background);
void Background_Destroy(struct Background* background);

#endif /* CLOCKWORKISLAND_BACKGROUND_H__ */
