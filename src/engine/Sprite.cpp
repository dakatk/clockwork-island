#include "engine/Sprite.h"
#include "engine/Viewport.h"
#include "engine/Window.h"

using namespace engine;

Sprite::Sprite(Texture* spritesheet, float x, float y, int width, int height)
{
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    this->rotation = 0;
    this->spriteClipX = 0;
    this->spriteClipY = 0;

    this->spritesheet = spritesheet;
    this->boundingBox = nullptr;
}

Sprite::~Sprite()
{
    delete this->boundingBox;
}

void Sprite::SetBoundingBox(float boundsWidth, float boundsHeight)
{
    float halfWidth = boundsWidth / 2.0f;
    float halfHeight = boundsHeight / 2.0f;

    float centerX = (float)this->x + ((float)this->width / 2.0f);
    float centerY = (float)this->y - ((float)this->height / 2.0f);

    this->boundingBox = new BoundingBox(centerX, centerY, halfWidth, halfHeight);
}

BoundingBox* Sprite::GetBoundingBox()
{
    return this->boundingBox;
}

void Sprite::Render()
{
    if (this->spritesheet == nullptr)
        return;

    this->spritesheet->MoveClip(this->spriteClipX, this->spriteClipY);

    int actualX = (int)(this->x - (float)Viewport::GetX());
    int actualY = (int)Window::GetBufferHeight() - (int)(this->y - (float)Viewport::GetY());

    if (this->rotation != 0)
        Window::RenderTextureRotated(*this->spritesheet, this->rotation, actualX, actualY, this->width, this->height);
    else
        Window::RenderTexture(*this->spritesheet, actualX, actualY, this->width, this->height);
}