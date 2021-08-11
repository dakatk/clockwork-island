#include "engine/Tile.h"
#include "engine/Viewport.h"
#include "engine/Window.h"

using namespace engine;

#define LEFT_BIT 3
#define RIGHT_BIT 1
#define BOTTOM_BIT 2

Tile::Tile(Texture* spritesheet, int rotation, int spriteClipX, int spriteClipY, uint8_t sides, int x, int y, int width, int height) : Sprite(spritesheet, (float)x, (float)y, width, height)
{
    this->spriteClipX = spriteClipX;
    this->spriteClipY = spriteClipY;
    this->rotation = rotation;
    this->sides = sides;
}

bool Tile::HasTop() const
{
    return (bool)(this->sides & 0x1);
}

bool Tile::HasLeft() const
{
    return (bool)((this->sides >> LEFT_BIT) & 0x1);
}

bool Tile::HasRight() const
{
    return (bool)((this->sides >> RIGHT_BIT) & 0x1);
}

bool Tile::HasBottom() const
{
    return (bool)((this->sides >> BOTTOM_BIT) & 0x1);
}

bool Tile::IsOffscreen()
{
    bool offscreenLeft = this->x > (float)(Viewport::GetX() + (int)Window::GetBufferWidth());
    bool offscreenRight = this->x + (float)this->width < (float)Viewport::GetX();
    bool offscreenAbove = this->y + (float)this->height > (float)(Viewport::GetY() + (int)Window::GetBufferHeight());
    bool offscreenBelow = this->y < (float)Viewport::GetY();

    return offscreenLeft || offscreenRight || offscreenAbove || offscreenBelow;
}