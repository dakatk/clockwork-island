#ifndef CLOCKWORKISLAND_BUFFER_H__
#define CLOCKWORKISLAND_BUFFER_H__

#include <SDL2/SDL.h>

#include "Bitmap.h"
#include "Filter.h"

#define BUFFER_WIDTH 800
#define BUFFER_HEIGHT 600

void Buffer_Init();// SDL_Renderer* renderer);

void Buffer_Begin();
void Buffer_Present();

void Buffer_BlitBitmap(struct Bitmap* bitmap, int x, int y, int w, int h);
void Buffer_BlitBitmapRotated(struct Bitmap* bitmap, double angle, int x, int y, int w, int h);
void Buffer_BlitBitmapFull(struct Bitmap* bitmap);
void Buffer_ApplyFilter(const struct Filter* filter);

void Buffer_Destroy();

#endif /* CLOCKWORKISLAND_BUFFER_H__ */
