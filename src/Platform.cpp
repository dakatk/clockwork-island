#include "Platform.h"
#include "Filter.h"

Platform::Platform(Texture *spritesheet, int angle, int spriteClipX, int spriteClipY, uint8_t sides, int x, int y, int width, int height)
: Tile(spritesheet, angle, spriteClipX, spriteClipY, sides, x, y, width, height)
{
    this->visible = 0x3F;
}

void Platform::SetVisibility(uint8_t visible_)
{
    this->visible = visible_;
}

bool Platform::IsVisible(uint8_t filter) const
{
    if (filter >= NUM_FILTERS)
        return true;

    return (bool)((this->visible >> filter) & 0x1);
}

