#include "engine/Buffer.h"

#include <SDL2/SDL.h>

static struct {
    SDL_Texture* texture;
    SDL_Renderer* renderer;
} buffer;

void Buffer_Init(SDL_Renderer* renderer)
{
    buffer.texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888,
                                       SDL_TEXTUREACCESS_TARGET, BUFFER_WIDTH, BUFFER_HEIGHT);
    buffer.renderer = renderer;
}

void Buffer_Begin()
{
    SDL_SetRenderTarget(buffer.renderer, buffer.texture);
}

void Buffer_Present()
{
    SDL_SetRenderTarget(buffer.renderer, NULL);
    SDL_RenderCopy(buffer.renderer, buffer.texture, NULL, NULL);
    SDL_RenderPresent(buffer.renderer);
}

static inline bool ClipFullImage(SDL_Rect clip)
{
    return clip.w == FULL_IMAGE || clip.h == FULL_IMAGE;
}

static void RenderRect(struct Texture* texture, SDL_Renderer* renderer, SDL_Rect* dest)
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
    RenderRect(texture, buffer.renderer, &dest);
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
    SDL_RenderCopyEx(buffer.renderer, texture->bitmap, &texture->clip, dest, angle, NULL, SDL_FLIP_NONE);
}

void Buffer_RenderTextureFull(struct Texture* texture)
{
    RenderRect(texture, buffer.renderer, NULL);
}

void Buffer_RenderFilter(const struct Filter* filter)
{
    SDL_SetRenderDrawColor(buffer.renderer, filter->r, filter->g,filter->b, FILTER_ALPHA);
    SDL_Rect screenBounds = {
            .x = 0,
            .y = 0,
            .w = BUFFER_WIDTH,
            .h = BUFFER_HEIGHT
    };
    SDL_RenderFillRect(buffer.renderer, &screenBounds);
}

void Buffer_Destroy()
{
    SDL_DestroyTexture(buffer.texture);
    SDL_DestroyRenderer(buffer.renderer);
}
