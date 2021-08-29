#ifndef ENGINE_WINDOW_H__
#define ENGINE_WINDOW_H__

#include "engine/Texture.h"
#include <SDL.h>
#include <string>

namespace engine
{
    class Window
    {
    private:
        static SDL_Window* window;
        static SDL_Texture* target;
        static SDL_Renderer* renderer;

        static unsigned int bufferWidth;
        static unsigned int bufferHeight;

    public:
        static void Create(const std::string &title, int bufferWidth, int bufferHeight);

        static unsigned int GetBufferWidth();
        static unsigned int GetBufferHeight();

        static SDL_Renderer* GetRenderingContext();

        static void ToggleFullscreen();

        static void RenderTexture(Texture& texture, int x, int y, int w, int h);
        static void RenderTextureRotated(Texture& texture, int angle, int x, int y, int w, int h);
        static void RenderFullScreenTexture(Texture& texture);

        static void RenderRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
        static void RenderFullScreenRect(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

        static void PresentBuffer();

        static void Destroy();
    };
}

#endif /* ENGINE_WINDOW_H__ */
