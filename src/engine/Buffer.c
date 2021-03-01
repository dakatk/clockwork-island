#include "Buffer.h"

#include <SDL2/SDL.h>

struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
};

static struct {
    struct Color* frame;
    // SDL_Texture* target;
    // SDL_Renderer* renderer;
} buffer;

void Buffer_Init()//SDL_Renderer* renderer)
{
    // buffer.target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
    //                                   SDL_TEXTUREACCESS_TARGET, BUFFER_WIDTH, BUFFER_HEIGHT);
    // buffer.renderer = renderer;
}

void Buffer_Begin()
{
    // SDL_SetRenderTarget(buffer.renderer, buffer.target);
}

void Buffer_Present()
{
    /*SDL_SetRenderTarget(buffer.renderer, NULL);
    SDL_RenderCopy(buffer.renderer, buffer.target, NULL, NULL);
    SDL_RenderPresent(buffer.renderer);*/
}

/*static inline bool ClipFullImage(SDL_Rect clip)
{
    return clip.w == FULL_IMAGE || clip.h == FULL_IMAGE;
}*/

static void RenderRect(struct Bitmap* bitmap, SDL_Renderer* renderer, SDL_Rect* dest)
{
    /*SDL_Rect* src = NULL;

    if (!(bit))
        src = &bitmap->clip;

    SDL_RenderCopy(renderer, bitmap->bitmap, src, dest);*/
}

void Buffer_BlitBitmap(struct Bitmap* bitmap, int x, int y, int w, int h)
{
    /*SDL_Rect dest = {
            .x = x,
            .y = y,
            .w = w,
            .h = h
    };
    RenderRect(bitmap, buffer.renderer, &dest);*/
}

void Buffer_BlitBitmapRotated(struct Bitmap* bitmap, double angle, int x, int y, int w, int h)
{
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
}

void Buffer_ApplyFilter(const struct Filter* filter)
{
    /*SDL_SetRenderDrawColor(buffer.renderer, filter->r, filter->g,filter->b, FILTER_ALPHA);
    SDL_Rect screenBounds = {
            .x = 0,
            .y = 0,
            .w = BUFFER_WIDTH,
            .h = BUFFER_HEIGHT
    };
    SDL_RenderFillRect(buffer.renderer, &screenBounds);*/
}

void Buffer_Destroy()
{
    /*SDL_DestroyTexture(buffer.target);
    SDL_DestroyRenderer(buffer.renderer);*/
}
