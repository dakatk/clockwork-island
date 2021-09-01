#include <engine/Player.h>
#include "game/platforms/Platform.h"
#include "game/Filter.h"

using namespace game;
using namespace platforms;

Platform::Platform(Texture* spritesheet, int rotation, int spriteClipX, int spriteClipY, uint8_t sides, int x, int y, int width, int height)
: Tile(spritesheet, rotation, spriteClipX, spriteClipY, sides, x, y, width, height)
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

void Platform::CollideTop(Sprite* entity)
{
    auto* player = dynamic_cast<Player*>(entity);
    if (player == nullptr)
        return;
    // auto* player = (Player*)entity;

    float platformTop = this->boundingBox->Top();
    float halfHeight = player->GetBoundingBox()->GetHalfHeight();

    player->GetBoundingBox()->SetCenterY(platformTop + halfHeight);
    player->SetVY(0.0f);
    player->SetJumping(false);
}

void Platform::CollideBottom(Sprite* entity)
{
    auto* player = dynamic_cast<Player*>(entity);
    if (player == nullptr)
        return;
    // auto* player = (Player*)entity;

    float platformBottom = this->boundingBox->Bottom();
    float halfHeight = player->GetBoundingBox()->GetHalfHeight();

    player->GetBoundingBox()->SetCenterY(platformBottom - halfHeight);
    player->SetVY(0.0f);
}

void Platform::CollideLeft(Sprite* entity)
{
    auto* player = dynamic_cast<Player*>(entity);
    if (player == nullptr)
        return;
    // auto* player = (Player*)entity;

    float platformLeft = this->boundingBox->Left();
    float halfWidth = player->GetBoundingBox()->GetHalfWidth();

    player->GetBoundingBox()->SetCenterX(platformLeft - halfWidth);
    player->SetVX(0.0f);
}

void Platform::CollideRight(Sprite* entity)
{
    auto* player = dynamic_cast<Player*>(entity);
    if (player == nullptr)
        return;
    // auto* player = (Player*)entity;

    float platformRight = this->boundingBox->Right();
    float halfWidth = player->GetBoundingBox()->GetHalfWidth();

    player->GetBoundingBox()->SetCenterX(platformRight + halfWidth);
    player->SetVX(0.0f);
}
