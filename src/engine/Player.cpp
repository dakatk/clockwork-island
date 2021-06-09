#include "engine/Player.h"
#include <cmath>

using namespace engine;

Player::Player(Texture *spritesheet, int x, int y, int width, int height) : Sprite(spritesheet, (float)x, (float)y, width, height)
{
    this->jumping = true;

    this->vx = 0.0f;
    this->vy = 0.0f;

    this->oldCX = (float)x + ((float)width / 2.0f);
    this->oldCY = (float)y + ((float)height / 2.0f);
}

float Player::GetVX() const
{
    return this->vx;
}

float Player::GetVY() const
{
    return this->vy;
}

void Player::ChangeVX(float dvx)
{
    this->vx += dvx;
}

void Player::ChangeVY(float dvy)
{
    this->vy += dvy;
}

void Player::SetJumping()
{
    this->jumping = true;
}

bool Player::IsJumping() const
{
    return this->jumping;
}

void Player::Move(float gravity, float friction, float maxJumpSpeed, float maxMoveSpeed, float minMoveSpeed)
{
    this->vy -= gravity;

    this->vy = fmaxf(fminf(this->vy, maxJumpSpeed), -maxJumpSpeed);
    this->vx = fmaxf(fminf(this->vx, maxMoveSpeed), -maxMoveSpeed);

    if (this->boundingBox != nullptr)
    {
        this->oldCX = this->boundingBox->GetCenterX();
        this->oldCY = this->boundingBox->GetCenterY();

        this->boundingBox->Move(this->vx, this->vy);

        this->x = this->boundingBox->GetCenterX() - ((float) this->width / 2.0f);
        this->y = this->boundingBox->GetCenterY() + ((float) this->height / 2.0f);
    }
    else
    {
        this->x += this->vx;
        this->y += this->vy;
    }
    this->vx *= friction;

    if (fabsf(this->vx) <= minMoveSpeed)
        this->vx = 0.0f;
}

void Player::Collide(Tile* platform)
{
    BoundingBox* platformBounds = platform->GetBoundingBox();
    BoundingBox* playerBounds = this->boundingBox;

    if (platformBounds == nullptr || playerBounds == nullptr)
        return;

    if (platform->HasTop())
    {
        float playerOldBottom = this->oldCY - playerBounds->GetHalfHeight();
        if (this->CollideTop(platformBounds->Top(), playerBounds->Bottom(), playerOldBottom))
            return;
    }

    if (platform->HasLeft())
    {
        float playerOldRight = this->oldCX + playerBounds->GetHalfWidth();
        if (this->CollideLeft(platformBounds->Left(), playerBounds->Right(), playerOldRight))
            return;
    }

    if (platform->HasRight())
    {
        float playerOldLeft = this->oldCX - playerBounds->GetHalfWidth();
        if (this->CollideRight(platformBounds->Right(), playerBounds->Left(), playerOldLeft))
            return;
    }

    if (platform->HasBottom())
    {
        float playerOldTop = this->oldCY + playerBounds->GetHalfHeight();
        if (this->CollideBottom(platformBounds->Bottom(), playerBounds->Top(), playerOldTop))
            return;
    }
}

bool Player::CollideTop(float platformTop, float playerBottom, float playerOldBottom)
{
    if (playerBottom < platformTop && playerOldBottom >= platformTop)
    {
        float halfHeight = this->boundingBox->GetHalfHeight();

        this->boundingBox->SetCenterY(platformTop + halfHeight);
        this->vy = 0.0f;
        this->jumping = false;

        return true;
    }
    return false;
}

bool Player::CollideLeft(float platformLeft, float playerRight, float playerOldRight)
{
    if (playerRight > platformLeft && playerOldRight <= platformLeft)
    {
        float halfWidth = this->boundingBox->GetHalfWidth();

        this->boundingBox->SetCenterX(platformLeft - halfWidth);
        this->vx = 0.0f;

        return true;
    }
    return false;
}

bool Player::CollideRight(float platformRight, float playerLeft, float playerOldLeft)
{
    if (playerLeft < platformRight && playerOldLeft >= platformRight)
    {
        float halfWidth = this->boundingBox->GetHalfWidth();

        this->boundingBox->SetCenterX(platformRight + halfWidth);
        this->vx = 0.0f;

        return true;
    }
    return false;
}

bool Player::CollideBottom(float platformBottom, float playerTop, float playerOldTop)
{
    if (playerTop > platformBottom && playerOldTop <= platformBottom)
    {
        float halfHeight = this->boundingBox->GetHalfHeight();

        this->boundingBox->SetCenterY(platformBottom - halfHeight);
        this->vy = 0.0f;

        return true;
    }
    return false;
}