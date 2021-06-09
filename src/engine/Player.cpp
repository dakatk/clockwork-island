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

Player::~Player()
{
    delete this->spritesheet;
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

        this->x = this->boundingBox->GetCenterX() - ((float)this->width / 2.0f);
        this->y = this->boundingBox->GetCenterY() + ((float)this->height / 2.0f);
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

void Player::MoveTo(int x, int y)
{
    this->x = (float)x;
    this->y = (float)y;

    this->boundingBox->SetCenterX(this->x + ((float)this->width / 2.0f));
    this->boundingBox->SetCenterY(this->y - ((float)this->height / 2.0f));
}

void Player::Collide(Tile* tile)
{
    BoundingBox* tileBounds = tile->GetBoundingBox();
    BoundingBox* playerBounds = this->boundingBox;

    if (tileBounds == nullptr || playerBounds == nullptr)
        return;

    if (tile->HasTop())
    {
        float playerOldBottom = this->oldCY - playerBounds->GetHalfHeight();
        if (this->CollideTop(tileBounds->Top(), playerBounds->Bottom(), playerOldBottom))
            return;
    }

    if (tile->HasLeft())
    {
        float playerOldRight = this->oldCX + playerBounds->GetHalfWidth();
        if (this->CollideLeft(tileBounds->Left(), playerBounds->Right(), playerOldRight))
            return;
    }

    if (tile->HasRight())
    {
        float playerOldLeft = this->oldCX - playerBounds->GetHalfWidth();
        if (this->CollideRight(tileBounds->Right(), playerBounds->Left(), playerOldLeft))
            return;
    }

    if (tile->HasBottom())
    {
        float playerOldTop = this->oldCY + playerBounds->GetHalfHeight();
        if (this->CollideBottom(tileBounds->Bottom(), playerBounds->Top(), playerOldTop))
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