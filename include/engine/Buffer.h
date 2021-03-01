#ifndef CLOCKWORKISLAND_BUFFER_H__
#define CLOCKWORKISLAND_BUFFER_H__

#include "Bitmap.h"
#include "Filter.h"

#define BUFFER_WIDTH 800
#define BUFFER_HEIGHT 600

// Pixels for each frame stored in RGBA order
extern unsigned char* frame;

void Buffer_Init();
void Buffer_BlitBitmap(struct Bitmap* bitmap, int x, int y);
void Buffer_BlitBitmapFlipped(struct Bitmap* bitmap, int x, int y);
void Buffer_BlitBitmapFull(struct Bitmap* bitmap);
void Buffer_ApplyFilter(const struct Filter* filter);
void Buffer_Destroy();

#endif /* CLOCKWORKISLAND_BUFFER_H__ */
