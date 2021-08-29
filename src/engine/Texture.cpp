#include "engine/Texture.h"
#include "engine/Window.h"
#include <iostream>

using namespace std;
using namespace engine;

Texture::Texture(const std::string& filename, int clipWidth, int clipHeight)
{
    SDL_Surface* image = IMG_Load(filename.c_str());

    if (image == nullptr)
    {
        SDL_FreeSurface(image);
        throw TextureLoadException("Failed to load image: " + filename);
    }
    this->bitmap = SDL_CreateTextureFromSurface(Window::GetRenderingContext(), image);

    this->bitmapWidth = 0;
    this->bitmapHeight = 0;

    SDL_QueryTexture(this->bitmap, nullptr, nullptr, &this->bitmapWidth, &this->bitmapHeight);

    this->clip.x = 0;
    this->clip.y = 0;
    this->clip.w = clipWidth;
    this->clip.h = clipHeight;
}

Texture::~Texture()
{
    SDL_DestroyTexture(this->bitmap);
}

SDL_Texture* Texture::GetBitmap()
{
    return this->bitmap;
}

SDL_Rect* Texture::GetClip()
{
    return &this->clip;
}

void Texture::MoveClip(int col, int row)
{
    this->clip.x = col * this->clip.h;
    this->clip.y = row * this->clip.w;
}

int Texture::GetBitmapWidth() const
{
    int bitmapWidth_;
    SDL_QueryTexture(this->bitmap, nullptr, nullptr, &bitmapWidth_, nullptr);

    return bitmapWidth_;
}

int Texture::GetBitmapHeight() const
{
    int bitmapHeight_;
    SDL_QueryTexture(this->bitmap, nullptr, nullptr, nullptr, &bitmapHeight_);

    return bitmapHeight_;
}
