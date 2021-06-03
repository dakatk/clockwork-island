#include "engine/Physics.h"

bool Physics_Intersects(struct BoundingBox* a, struct BoundingBox* b)
{
    float xDiff = fabsf(a->cx - b->cx);
    float yDiff = fabsf(a->cy - b->cy);

    return xDiff < (a->halfWidth + b->halfWidth) &&
            yDiff < (a->halfHeight + b->halfHeight);
}

void Physics_MovePlayer(struct Player* player, float gravity, float friction, float maxJumpSpeed, float maxMoveSpeed, float minMoveSpeed)
{
    player->oldCX = player->boundingBox.cx;
    player->oldCY = player->boundingBox.cy;

    player->vy -= gravity;

    player->vy = fmaxf(fminf(player->vy, maxJumpSpeed), -maxJumpSpeed);
    player->vx = fmaxf(fminf(player->vx, maxMoveSpeed), -maxMoveSpeed);

    player->boundingBox.cx += player->vx;
    player->boundingBox.cy += player->vy;

    player->x = player->boundingBox.cx - ((float)player->w / 2.0f);
    player->y = player->boundingBox.cy + ((float)player->h / 2.0f);

    player->vx *= friction;

    if (fabsf(player->vx) <= minMoveSpeed)
        player->vx = 0.0f;
}

static bool CollideTop(struct Player* player, float platformTop, float playerBottom, float playerOldBottom);
static bool CollideLeft(struct Player* player, float platformLeft, float playerRight, float playerOldRight);
static bool CollideRight(struct Player* player, float platformRight, float playerLeft, float playerOldLeft);
static void CollideBottom(struct Player* player, float platformBottom, float playerTop, float playerOldTop);

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
        float platformTop = platformBounds->cy + platformBounds->halfHeight;
        float playerBottom = playerBounds->cy - playerBounds->halfHeight;
        float playerOldBottom = player->oldCY - playerBounds->halfHeight;

        if (CollideTop(player, platformTop, playerBottom, playerOldBottom))
            return;
    }

    if (hasLeft)
    {
        float platformLeft = platformBounds->cx - platformBounds->halfWidth;
        float playerRight = playerBounds->cx + playerBounds->halfWidth;
        float playerOldRight = player->oldCX + playerBounds->halfWidth;

        if (CollideLeft(player, platformLeft, playerRight, playerOldRight))
            return;
    }

    if (hasRight)
    {
        float platformRight = platformBounds->cx + platformBounds->halfWidth;
        float playerLeft = playerBounds->cx - playerBounds->halfWidth;
        float playerOldLeft = player->oldCX - playerBounds->halfWidth;

        if (CollideRight(player, platformRight, playerLeft, playerOldLeft))
            return;
    }

    if (hasBottom)
    {
        float platformBottom = platformBounds->cy - platformBounds->halfHeight;
        float playerTop = playerBounds->cy + playerBounds->halfHeight;
        float playerOldTop = player->oldCY + playerBounds->halfHeight;

        CollideBottom(player, platformBottom, playerTop, playerOldTop);
    }
}

static bool CollideTop(struct Player* player, float platformTop, float playerBottom, float playerOldBottom)
{
    if (playerBottom < platformTop && playerOldBottom >= platformTop)
    {
        float halfHeight = player->boundingBox.halfHeight;

        player->boundingBox.cy = platformTop + halfHeight;
        player->vy = 0.0f;
        player->isJumping = false;

        return true;
    }
    return false;
}

static bool CollideLeft(struct Player* player, float platformLeft, float playerRight, float playerOldRight)
{
    if (playerRight > platformLeft && playerOldRight <= platformLeft)
    {
        float halfWidth = player->boundingBox.halfWidth;

        player->boundingBox.cx = platformLeft - halfWidth;
        player->vx = 0.0f;

        return true;
    }
    return false;
}

static bool CollideRight(struct Player* player, float platformRight, float playerLeft, float playerOldLeft)
{
    if (playerLeft < platformRight && playerOldLeft >= platformRight)
    {
        float halfWidth = player->boundingBox.halfWidth;

        player->boundingBox.cx = platformRight + halfWidth;
        player->vx = 0.0f;

        return true;
    }
    return false;
}

static void CollideBottom(struct Player* player, float platformBottom, float playerTop, float playerOldTop)
{
    if (playerTop > platformBottom && playerOldTop <= platformBottom)
    {
        float halfHeight = player->boundingBox.halfHeight;

        player->boundingBox.cy = platformBottom - halfHeight;
        player->vy = 0.0f;
    }
}
