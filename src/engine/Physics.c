#include "engine/Physics.h"

static bool collideLeft(struct Player* player, float platformLeft, float playerOldRight);
static bool collideRight(struct Player* player, float platformRight, float playerOldLeft);

void Physics_Collide(struct Player* player, struct Platform* platform, float playerOldX, float playerOldY)
{
    uint8_t hasTop = platform->sides & 0x1;
    uint8_t hasRight = (platform->sides >> 1) & 0x1;
    uint8_t hasBottom = (platform->sides >> 2) & 0x1;
    uint8_t hasLeft = (platform->sides >> 3) & 0x1;

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
        float playerOldLeft = playerOldX;

        if (collideRight(player, platformRight, playerOldLeft))
            return;
    }
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
    float playerLeft = player->x;

    if (playerLeft < platformRight && playerOldLeft >= platformRight)
    {
        player->x = platformRight;
        player->vx = 0.0f;

        return true;
    }
    return false;
}
