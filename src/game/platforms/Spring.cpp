#include "game/platforms/Spring.h"
#include "engine/Player.h"

#define BOUNCE_SPEED 11.5f

#define SPRITE_CLIP_START_X 3
#define SPRITE_CLIP_START_Y 3
#define SPRITE_CLIP_END_X 5

#define ANIM_TIMER_SHORT_TICKS 17
#define ANIM_TIMER_LONG_TICKS 200

using namespace game;
using namespace platforms;

Spring::Spring(Texture* spritesheet, int rotation, uint8_t sides, int x, int y, int width, int height)
    : Platform(spritesheet, rotation, SPRITE_CLIP_START_X, SPRITE_CLIP_START_Y, sides, x, y, width, height)
{
    this->animTimer = Timer();
    this->animWait = ANIM_TIMER_SHORT_TICKS;
    this->animDirection = 1;
    this->activated = false;
}

void Spring::CollideTop(Sprite* entity)
{
    Platform::CollideTop(entity);

    auto* player = dynamic_cast<Player*>(entity);
    if (player == nullptr)
        return;

    // TODO bounce is good, but needs quicker decel (?)
    player->SetJumping(true);
    player->SetVY(BOUNCE_SPEED);

    this->animTimer.Start();
    this->spriteClipX = SPRITE_CLIP_START_X + 1;
    this->activated = true;
}

void Spring::SetBoundingBox(float boundsWidth, float boundsHeight)
{
    float halfWidth = boundsWidth / 2.0f;
    float halfHeight = boundsHeight / 2.0f;

    float centerX = (float)this->x + ((float)this->width / 2.0f);
    float centerY = (float)this->y - ((float)this->height - halfHeight);

    this->boundingBox = new BoundingBox(centerX, centerY, halfWidth, halfHeight);
}

void Spring::Animate()
{
    if (this->IsOffscreen())
    {
        this->activated = false;
        this->animDirection = 1;
        this->animWait = ANIM_TIMER_SHORT_TICKS;
        this->spriteClipX = SPRITE_CLIP_START_X;

        return;
    }
    else if (!this->activated)
        return;

    else if (this->animTimer.Ticks() >= this->animWait)
    {
        this->spriteClipX += this->animDirection;

        if (this->spriteClipX == SPRITE_CLIP_END_X)
        {
            this->animWait = ANIM_TIMER_LONG_TICKS;
            this->animDirection = -1;
        }

        else if (this->spriteClipX == SPRITE_CLIP_START_X)
        {
            this->activated = false;
            this->animDirection = 1;
            this->animWait = ANIM_TIMER_SHORT_TICKS;
        }
        this->animTimer.Start();
    }
}