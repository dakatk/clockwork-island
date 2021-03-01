#include "engine/Buffer.h"

#include <stdlib.h>

unsigned char* frame;

void Buffer_Init()//SDL_Renderer* renderer)
{
    // buffer.target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
    //                                   SDL_TEXTUREACCESS_TARGET, BUFFER_WIDTH, BUFFER_HEIGHT);
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

void Buffer_BlitBitmapRotated(struct Bitmap* bitmap, double angle, int x, int y)
{
    // TODO
    /*SDL_Rect* dest = NULL;

    if (!clipFullImage(bitmap->clip))
    {
        SDL_Rect clip = {
                .x = x,
                .y = y,
                .w = w,
                .h = h
        };
        dest = &clip;
    }
    SDL_RenderCopyEx(buffer.renderer, bitmap->bitmap, &bitmap->clip, dest, angle, NULL, SDL_FLIP_NONE);*/
}

void Buffer_BlitBitmapFull(struct Bitmap* bitmap)
{
    // RenderRect(bitmap, buffer.renderer, NULL);
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
