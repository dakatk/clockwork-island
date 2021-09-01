#include "game/platforms/Spring.h"
#include "engine/Player.h"

#define BOUNCE_SPEED 10.5f

#define SPRITE_CLIP_START_X 3
#define SPRITE_CLIP_END_X 5

using namespace game;
using namespace platforms;

void Spring::CollideTop(Sprite* entity)
{
    Platform::CollideTop(entity);

    auto* player = dynamic_cast<Player*>(entity);
    if (player == nullptr)
        return;

    player->SetJumping(true);
    player->ChangeVY(BOUNCE_SPEED);

    this->spriteClipX = 5;
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

}