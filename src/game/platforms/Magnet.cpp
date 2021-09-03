#include "game/platforms/Magnet.h"

#define SPRITE_CLIP_START_X 0
#define SPRITE_CLIP_START_Y 3
#define SPRITE_CLIP_END_X 2

#define ANIM_WAIT 100

using namespace game::platforms;

Magnet::Magnet(Texture* spritesheet, int rotation, uint8_t sides, int x, int y, int width, int height)
    : Platform(spritesheet, rotation, SPRITE_CLIP_START_X, SPRITE_CLIP_START_Y, sides, x, y, width, height)
{
    this->animTimer = Timer();
    this->animTimer.Start();
}

void Magnet::Animate()
{
    if (this->animTimer.Ticks() >= ANIM_WAIT)
    {
        this->spriteClipX ++;
        if (this->spriteClipX > SPRITE_CLIP_END_X)
            this->spriteClipX = 0;

        this->animTimer.Start();
    }
}
