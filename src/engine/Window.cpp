#include "engine/Window.h"
#include <SDL_image.h>
#include <iostream>

using namespace std;
using namespace engine;

SDL_Window* Window::window;
SDL_Texture* Window::target;
SDL_Renderer* Window::renderer;

unsigned int Window::bufferWidth;
unsigned int Window::bufferHeight;

void Window::Create(const string& title, int bufferWidth_, int bufferHeight_)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cerr << "Failed to initialize video context" << endl;
        exit(1);
    }

    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              bufferWidth_, bufferHeight_, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (window == nullptr)
    {
        cerr << "Failed to create window" << endl;

        SDL_Quit();
        exit(1);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        cerr << "Failed to create rendering context" << endl;

        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    SDL_RaiseWindow(window);

    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
    {
        cerr << "Failed to initialize image context" << endl;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
    SDL_RenderClear(renderer);

    target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (int)bufferWidth_, (int)bufferHeight_);

    if (target == nullptr)
    {
        cerr << "Failed to create backbuffer" << endl;

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(1);
    }
    bufferWidth = bufferWidth_;
    bufferHeight = bufferHeight_;
}

unsigned int Window::GetBufferWidth()
{
    return bufferWidth;
}

unsigned int Window::GetBufferHeight()
{
    return bufferHeight;
}

SDL_Renderer* Window::GetRenderingContext()
{
    return renderer;
}

void Window::ToggleFullscreen()
{
    bool isFullscreen = SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN;
    SDL_SetWindowFullscreen(window, isFullscreen ? 0 : SDL_WINDOW_FULLSCREEN);
}

static inline bool ClipFullImage(SDL_Rect* clip)
{
    return clip->w == FULL_IMAGE || clip->h == FULL_IMAGE;
}

static void RenderRect_(SDL_Renderer* renderer, Texture& texture, SDL_Rect* dest)
{
    SDL_Rect* clip = texture.GetClip();
    SDL_Rect* src = nullptr;

    if (!ClipFullImage(clip))
        src = clip;

    SDL_RenderCopy(renderer, texture.GetBitmap(), src, dest);
}

void Window::RenderTexture(Texture& texture, int x, int y, int w, int h)
{
    SDL_SetRenderTarget(renderer, target);

    SDL_Rect dest = {
            .x = x,
            .y = y,
            .w = w,
            .h = h
    };
    RenderRect_(renderer, texture, &dest);
}

void Window::RenderTextureRotated(Texture& texture, int angle, int x, int y, int w, int h)
{
    SDL_SetRenderTarget(renderer, target);

    SDL_Rect* clip = texture.GetClip();
    SDL_Rect* dest = nullptr;
    SDL_Rect destClip;

    if (!ClipFullImage(clip))
    {
        destClip = {
                .x = x,
                .y = y,
                .w = w,
                .h = h
        };
        dest = &destClip;
    }
    SDL_RenderCopyEx(renderer, texture.GetBitmap(), clip, dest, angle, nullptr, SDL_FLIP_NONE);
}

void Window::RenderFullScreenTexture(Texture& texture)
{
    SDL_SetRenderTarget(renderer, target);
    RenderRect_(renderer, texture, nullptr);
}

void Window::RenderRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderTarget(renderer, target);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    SDL_Rect dest = {
            .x = x,
            .y = y,
            .w = w,
            .h = h
    };
    SDL_RenderDrawRect(renderer, &dest);
}

void Window::RenderFilledRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    SDL_SetRenderTarget(renderer, target);
    SDL_SetRenderDrawColor(renderer, r, g, b, a);

    SDL_Rect dest = {
            .x = x,
            .y = y,
            .w = w,
            .h = h
    };
    SDL_RenderFillRect(renderer, &dest);
}

void Window::RenderFullScreenRect(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    Window::RenderFilledRect(0, 0, (int)bufferWidth, (int)bufferHeight, r, g, b, a);
}

void Window::PresentBuffer()
{
    SDL_SetRenderTarget(renderer, nullptr);
    SDL_RenderCopy(renderer, target, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void Window::Destroy()
{
    SDL_ClearHints();

    SDL_DestroyTexture(target);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();
}