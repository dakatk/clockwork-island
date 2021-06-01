#include "engine/Physics.h"

static bool collideTop(struct Player* player, float platformTop, float playerOldBottom);
static bool collideLeft(struct Player* player, float platformLeft, float playerOldRight);
static bool collideRight(struct Player* player, float platformRight, float playerOldLeft);
static void collideBottom(struct Player* player, float platformBottom, float playerOldTop);

void Physics_Collide(struct Player* player, struct Platform* platform, float playerOldX, float playerOldY)
{
    uint8_t hasTop = platform->sides & 0x1;
    uint8_t hasRight = (platform->sides >> 1) & 0x1;
    uint8_t hasBottom = (platform->sides >> 2) & 0x1;
    uint8_t hasLeft = (platform->sides >> 3) & 0x1;

    if (hasTop)
    {
        float platformTop = (float)platform->y;
        float playerOldBottom = playerOldY + (float)player->h;

        if (collideTop(player, platformTop, playerOldBottom))
            return;
    }

    if (hasLeft)
    {
        float platformLeft = (float)platform->x;
        float playerOldRight = playerOldX + (float)player->w;

        if (collideLeft(player, platformLeft, playerOldRight))
            return;
    }

    if (hasRight)
    {
        float platformRight = (float)(platform->x + platform->w);
        if (collideRight(player, platformRight, playerOldX))
            return;
    }

    if (hasBottom)
    {
        float platformBottom = (float)(platform->y + platform->w);
        collideBottom(player, platformBottom, playerOldY);
    }
}

static bool collideTop(struct Player* player, float platformTop, float playerOldBottom)
{
    float playerBottom = player->y + (float)player->h;

    if (playerBottom > platformTop && playerOldBottom <= platformTop)
    {
        player->y = platformTop - (float)player->h;
        player->vy = 0.0f;
        player->isJumping = false;

        return true;
    }
    return false;
}

static bool collideLeft(struct Player* player, float platformLeft, float playerOldRight)
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

static bool collideRight(struct Player* player, float platformRight, float playerOldLeft)
{
    if (player->x < platformRight && playerOldLeft >= platformRight)
    {
        player->x = platformRight;
        player->vx = 0.0f;

        return true;
    }
    return false;
}

static void collideBottom(struct Player* player, float platformBottom, float playerOldTop)
{
    if (player->y < platformBottom && playerOldTop >= platformBottom)
    {
        player->y = platformBottom;
        player->vy = 0.0f;
    }
}
