#ifndef ENGINE_TEXTURE_H__
#define ENGINE_TEXTURE_H__

#include <SDL.h>
#include <SDL_image.h>
#include <string>

#define FULL_IMAGE (-1)

namespace engine
{
    class Texture
    {
    private:
        SDL_Texture* bitmap;
        SDL_Rect clip{};

        int bitmapWidth;
        int bitmapHeight;

    public:
        Texture(const std::string &filename, int clipWidth, int clipHeight);
        ~Texture();

        SDL_Texture* GetBitmap();
        SDL_Rect* GetClip();
        void MoveClip(int col, int row);

        int GetBitmapWidth() const;
        int GetBitmapHeight() const;
    };

    class TextureLoadException : public std::exception {
    private:
        std::string message;
    public:
        explicit TextureLoadException(std::string message_) : message(std::move(message_)) {}
        const char* what() const noexcept override { return message.c_str(); }
    };
}

#endif /* ENGINE_TEXTURE_H__ */
