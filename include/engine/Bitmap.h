#ifndef CLOCKWORKISLAND_TEXTURE_H__
#define CLOCKWORKISLAND_TEXTURE_H__

#include <SDL2/SDL.h>
#include "Bool.h"

#define FULL_IMAGE -1

struct Bitmap {
    unsigned char* pixels;

    int clipX, clipY;
    int clipSize;
    int w, h;
};

void Bitmap_Init(struct Bitmap* bitmap, unsigned char* pixels, int w, int h, int clipSize);
void Bitmap_MoveClip(struct Bitmap* bitmap, int col, int row);
void Bitmap_Destroy(struct Bitmap* texture);

#endif /* CLOCKWORKISLAND_TEXTURE_H__ */
