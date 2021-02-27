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

void Buffer_RenderTexture(struct Texture* texture, int x, int y, int w, int h);
void Buffer_RenderTextureRotated(struct Texture* texture, double angle, int x, int y, int w, int h);
void Buffer_RenderTextureFull(struct Texture* texture);
void Buffer_RenderFilter(const struct Filter* filter);

void Buffer_Destroy();

#endif /* CLOCKWORKISLAND_BUFFER_H__ */
