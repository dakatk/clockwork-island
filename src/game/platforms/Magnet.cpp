#include "game/platforms/Magnet.h"
#include "engine/Player.h"

#define SPRITE_CLIP_START_X 0
#define SPRITE_CLIP_START_Y 3
#define SPRITE_CLIP_END_X 2

#define ANIM_WAIT 100

#define FIELD_STRENGTH 80

using namespace game::platforms;

Magnet::Magnet(Texture* spritesheet, int rotation, uint8_t sides, int x, int y, int width, int height)
    : Platform(spritesheet, rotation, SPRITE_CLIP_START_X, SPRITE_CLIP_START_Y, sides, x, y, width, height)
{
    this->animTimer = Timer();
    this->animTimer.Start();

    float centerX = this->boundingBox->GetCenterX();
    float centerY = this->boundingBox->GetCenterY();

    float halfWidth = this->boundingBox->GetHalfWidth() + FIELD_STRENGTH;
    float halfHeight = this->boundingBox->GetHalfHeight() + FIELD_STRENGTH;

    this->field = BoundingBox(centerX, centerY, halfWidth, halfHeight);
}

void Magnet::Effect(Sprite* sprite)
{
    auto* player = dynamic_cast<Player*>(sprite);
    if (player == nullptr)
        return;

    BoundingBox* playerBounds = player->GetBoundingBox();
    if (playerBounds->Intersects(&this->field))
    {
        // TODO push/pull physics based on rotation and player's polarity (?)
    }
}

bool Magnet::IsApplicable(uint8_t filter)
{
    return !this->IsOffscreen() && this->IsVisible(filter);
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
