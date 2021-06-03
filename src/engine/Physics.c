#include "engine/Physics.h"

bool Physics_Intersects(struct BoundingBox* a, struct BoundingBox* b)
{
    /*float playerCenterX = player->x + ((float)player->w / 2.0f);
    float playerCenterY = player->y - ((float)player->h / 2.0f);

    float platformCenterX = (float)platform->x + ((float)platform->w / 2.0f);
    float platformCenterY = (float)platform->y - ((float)platform->h / 2.0f);*/

    float xDiff = fabsf(a->cx - b->cx) * 2.0f;
    float yDiff = fabsf(a->cy - b->cy) * 2.0f;

    return xDiff < (float)(a->halfWidth + b->halfWidth) * 2.0f &&
            yDiff < (float)(a->halfHeight + b->halfHeight) * 2.0f;
}

void Physics_MovePlayer(struct Player* player, float gravity, float friction, float maxJumpSpeed, float maxMoveSpeed, float minMoveSpeed)
{
    player->oldCX = player->boundingBox.cx;
    player->oldCY = player->boundingBox.cy;

    player->vy -= gravity;

    player->vy = fmaxf(fminf(player->vy, maxJumpSpeed), -maxJumpSpeed);
    player->vx = fmaxf(fminf(player->vx, maxMoveSpeed), -maxMoveSpeed);

    player->x += player->vx;
    player->y += player->vy;

    player->boundingBox.cx = player->x + ((float)player->w / 2.0f);
    player->boundingBox.cy = player->y - ((float)player->h / 2.0f);

    player->vx *= friction;

    if (fabsf(player->vx) <= minMoveSpeed)
        player->vx = 0.0f;
}

static bool CollideTop(struct Player* player, float platformTop, float playerOldBottom);
static bool CollideLeft(struct Player* player, float platformLeft, float playerOldRight);
static bool CollideRight(struct Player* player, float platformRight, float playerOldLeft);
static void CollideBottom(struct Player* player, float platformBottom, float playerOldTop);

// TODO FUTURE Add support for minimum step height?
void Physics_Collide(struct Player* player, struct Platform* platform)
{
    uint8_t hasTop = platform->sides & 0x1;
    uint8_t hasRight = (platform->sides >> 1) & 0x1;
    uint8_t hasBottom = (platform->sides >> 2) & 0x1;
    uint8_t hasLeft = (platform->sides >> 3) & 0x1;

    struct BoundingBox* playerBounds = &player->boundingBox;
    struct BoundingBox* platformBounds = &platform->boundingBox;

    if (hasTop)
    {
        float platformTop = platformBounds->cy + platformBounds->halfHeight;// (float)platform->y;
        float playerOldBottom = player->oldCY - playerBounds->halfHeight;//player->oldY - (float)player->h;

        if (CollideTop(player, platformTop, playerOldBottom))
            return;
    }

    if (hasLeft)
    {
        float platformLeft = platformBounds->cx - platformBounds->halfWidth;// (float)platform->x;
        float playerOldRight = player->oldCX + playerBounds->halfWidth;// player->oldX + (float)player->w;

        if (CollideLeft(player, platformLeft, playerOldRight))
            return;
    }

    if (hasRight)
    {
        float platformRight = platformBounds->cx + platformBounds->halfWidth;// (float)(platform->x + platform->w);
        float playerOldLeft = player->oldCX - playerBounds->halfWidth;

        if (CollideRight(player, platformRight, playerOldLeft))
            return;
    }

    if (hasBottom)
    {
        float platformBottom = platformBounds->cy - platformBounds->halfHeight;// (float)(platform->y - platform->h);
        float playerOldTop = player->oldCY + playerBounds->halfHeight;

        CollideBottom(player, platformBottom, playerOldTop);
    }
}

static bool CollideTop(struct Player* player, float platformTop, float playerOldBottom)
{
    float playerBottom = player->y - (float)player->h;

    if (playerBottom < platformTop && playerOldBottom >= platformTop)
    {
        player->y = platformTop + (float)player->h;
        player->vy = 0.0f;
        player->isJumping = false;

        return true;
    }
    return false;
}

static bool CollideLeft(struct Player* player, float platformLeft, float playerOldRight)
{
    float playerRight = player->x + (float)player->w;

    if (playerRight > platformLeft && playerOldRight <= platformLeft)
    {
        player->x = platformLeft - (float)player->w;
        player->vx = 0.0f;

        return true;
    }
    return false;
}

static bool CollideRight(struct Player* player, float platformRight, float playerOldLeft)
{
    if (player->x < platformRight && playerOldLeft >= platformRight)
    {
        player->x = platformRight;
        player->vx = 0.0f;

        return true;
    }
    return false;
}

static void CollideBottom(struct Player* player, float platformBottom, float playerOldTop)
{
    if (player->y > platformBottom && playerOldTop <= platformBottom)
    {
        player->y = platformBottom;
        player->vy = 0.0f;
    }
}
