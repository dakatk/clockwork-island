#include "engine/Buffer.h"

#include <SDL2/SDL.h>

static SDL_Texture* target;
static SDL_Renderer* renderer;

void Buffer_Init(SDL_Renderer* renderer_)
{
    target = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, BUFFER_WIDTH, BUFFER_HEIGHT);
    renderer = renderer_;
}

void Buffer_Begin()
{
    SDL_SetRenderTarget(renderer, target);
}

void Buffer_Present()
{
    SDL_SetRenderTarget(renderer, NULL);
    SDL_RenderCopy(renderer, target, NULL, NULL);
    SDL_RenderPresent(renderer);
}

static inline bool ClipFullImage(SDL_Rect clip)
{
    return clip.w == FULL_IMAGE || clip.h == FULL_IMAGE;
}

static void RenderRect(struct Texture* texture, SDL_Rect* dest)
{
    SDL_Rect* src = NULL;

    if (!ClipFullImage(texture->clip))
        src = &texture->clip;

    SDL_RenderCopy(renderer, texture->bitmap, src, dest);
}

void Buffer_RenderTexture(struct Texture* texture, int x, int y, int w, int h)
{
    SDL_Rect dest = {
            .x = x,
            .y = y,
            .w = w,
            .h = h
    };
    RenderRect(texture, &dest);
}

void Buffer_RenderTextureRotated(struct Texture* texture, double angle, int x, int y, int w, int h)
{
    SDL_Rect* dest = NULL;

    if (!ClipFullImage(texture->clip))
    {
        SDL_Rect clip = {
                .x = x,
                .y = y,
                .w = w,
                .h = h
        };
        dest = &clip;
    }
    SDL_RenderCopyEx(renderer, texture->bitmap, &texture->clip, dest, angle, NULL, SDL_FLIP_NONE);
}

void Buffer_RenderTextureFull(struct Texture* texture)
{
    RenderRect(texture, NULL);
}

void Buffer_RenderFilter(const struct Filter* filter)
{
    SDL_SetRenderDrawColor(renderer, filter->r, filter->g,filter->b, FILTER_ALPHA);
    SDL_Rect screenBounds = {
            .x = 0,
            .y = 0,
            .w = BUFFER_WIDTH,
            .h = BUFFER_HEIGHT
    };
    SDL_RenderFillRect(renderer, &screenBounds);
}

void Buffer_Destroy()
{
    SDL_DestroyTexture(target);
    SDL_DestroyRenderer(renderer);
}
