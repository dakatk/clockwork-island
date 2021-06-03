#ifndef CLOCKWORKISLAND_BUFFER_H__
#define CLOCKWORKISLAND_BUFFER_H__

#include "Texture.h"
#include "Filter.h"

#include <SDL.h>

void Buffer_Init(SDL_Renderer* renderer, int w, int h);
void Buffer_Begin();
void Buffer_Present();
void Buffer_RenderTexture(struct Texture* texture, int x, int y, int w, int h);
void Buffer_RenderTextureRotated(struct Texture* texture, double angle, int x, int y, int w, int h);
void Buffer_RenderTextureFull(struct Texture* texture);
void Buffer_RenderFilter(const struct Filter* filter);
void Buffer_Destroy();

#endif /* CLOCKWORKISLAND_BUFFER_H__ */
