#include "engine/Bitmap.h"

#include <stdlib.h>
#include <string.h>

void Bitmap_Init(struct Bitmap* bitmap, unsigned char* pixels, int w, int h, int clipSize)
{
    size_t pixelsSize = w * h * 4 * sizeof(unsigned char);

    bitmap->pixels = malloc(pixelsSize);
    memcpy(bitmap->pixels, pixels, pixelsSize);

    bitmap->w = w;
    bitmap->h = h;
    bitmap->clipX = 0;
    bitmap->clipY = 0;
    bitmap->clipSize = clipSize;
}

void Bitmap_MoveClip(struct Bitmap* bitmap, int col, int row)
{
    bitmap->clipX = col * bitmap->clipSize;
    bitmap->clipY = row * bitmap->clipSize;
}

void Bitmap_Destroy(struct Bitmap* texture)
{
	free(texture->pixels);
}
