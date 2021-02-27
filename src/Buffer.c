#include "Buffer.h"

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
    SDL_RenderCopy(buffer.renderer, buffer.texture, NULL, NULL);
    SDL_RenderPresent(buffer.renderer);
}

void Buffer_RenderTexture(struct Texture* texture, int x, int y, int w, int h)
{
    Texture_Render(texture, buffer.renderer, x, y, w, h);
}

void Buffer_RenderTextureRotated(struct Texture* texture, double angle, int x, int y, int w, int h)
{
    Texture_RenderRotated(texture, angle, x, y, w, h);
}

void Buffer_RenderTextureFull(struct Texture* texture)
{
    Texture_RenderFull(texture, buffer.renderer);
}

void Buffer_RenderFilter(const struct Filter* filter)
{
    Filter_Render(filter, buffer.renderer);
}

void Buffer_Destroy()
{
    SDL_DestroyTexture(buffer.texture);
    SDL_DestroyRenderer(buffer.renderer);
}
