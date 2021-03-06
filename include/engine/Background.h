#ifndef CLOCKWORKISLAND_BACKGROUND_H__
#define CLOCKWORKISLAND_BACKGROUND_H__

#include "Texture.h"

bool Background_Init(SDL_Renderer* renderer, const char* image0, const char* image1);
void Background_Scroll();
void Background_Render();
void Background_Destroy();

#endif /* CLOCKWORKISLAND_BACKGROUND_H__ */
