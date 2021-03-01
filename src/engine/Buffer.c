#include "engine/Buffer.h"

#include <stdlib.h>

unsigned char* frame;

void Buffer_Init()
{
    frame = malloc(BUFFER_WIDTH * BUFFER_HEIGHT * sizeof(unsigned char) * 4);
}

void Buffer_BlitBitmap(struct Bitmap* bitmap, int x, int y)
{
    int startX = 0;
    int startY = 0;
    int endX = bitmap->w;
    int endY = bitmap->h;

    if (bitmap->clipSize != FULL_IMAGE)
    {
        startX = bitmap->clipX;
        startY = bitmap->clipY;
        endX = bitmap->clipSize;
        endY = bitmap->clipSize;
    }

    for (int row = 0; row < endY; row ++)
    {
        int bitmapRow = row + startY;
        int bufferRow = row + y;

        if (bitmapRow < 0 || bitmapRow >= bitmap->h)
            continue;

        if (bufferRow < 0 || bufferRow >= BUFFER_HEIGHT)
            continue;

        // TODO replace with memcpy
        for (int col = 0; col < endX; col ++)
        {
            int bitmapCol = col + startX;
            int bufferCol = col + x;

            if (bitmapCol < 0 || bitmapCol >= bitmap->w)
                continue;

            if (bufferCol < 0 || bufferCol >= BUFFER_WIDTH)
                continue;

            int bitmapIndex = bitmapRow * bitmap->w + bitmapCol;
            int bufferIndex = bufferRow * BUFFER_WIDTH + bufferCol;

            unsigned char alpha = frame[(bufferIndex * 4) + 3];
            if (alpha == 0)
                continue;

            memcpy(frame + (bufferIndex * 4), bitmap->pixels + (bitmapIndex * 4), 4 * sizeof(unsigned char));
        }
    }

}

void Buffer_BlitBitmapFlipped(struct Bitmap* bitmap, int x, int y)
{
    // TODO same as BlitBitmap, but starting from the bottom (flipped y-coord)
}

void Buffer_BlitBitmapFull(struct Bitmap* bitmap)
{
    Buffer_BlitBitmap(bitmap, 0, 0);
}

void Buffer_ApplyFilter(const struct Filter* filter)
{
    for (int row = 0; row < BUFFER_HEIGHT; row ++)
    {
        for (int col = 0; col < BUFFER_WIDTH; col ++)
        {
            // TODO color combine
        }
    }
}

void Buffer_Destroy()
{
    free(frame);
}
