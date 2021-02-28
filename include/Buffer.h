#ifndef CLOCKWORKISLAND_BUFFER_H__
#define CLOCKWORKISLAND_BUFFER_H__

#include <SDL2/SDL.h>

#include "Texture.h"
#include "Filter.h"

#define BUFFER_WIDTH 800
#define BUFFER_HEIGHT 600

void Buffer_Init(SDL_Renderer* renderer);

void Buffer_Begin();
void Buffer_Present();

void Buffer_BlitTexture(struct Texture* texture, int x, int y, int w, int h);
void Buffer_BlitTextureRotated(struct Texture* texture, double angle, int x, int y, int w, int h);
void Buffer_BlitTextureFull(struct Texture* texture);
void Buffer_ApplyFilter(const struct Filter* filter);

void Buffer_Destroy();

#endif /* CLOCKWORKISLAND_BUFFER_H__ */
