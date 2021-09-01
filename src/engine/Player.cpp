#include "engine/Player.h"
#include <cmath>

using namespace engine;

Player::Player(Texture* spritesheet, int x, int y, int width, int height) : Sprite(spritesheet, (float)x, (float)y, width, height)
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

void Player::SetVX(float _vx)
{
    this->vx = _vx;
}

void Player::SetVY(float _vy)
{
    this->vy = _vy;
}

void Player::ChangeVX(float dvx)
{
    this->vx += dvx;
}

void Player::ChangeVY(float dvy)
{
    this->vy += dvy;
}

void Player::SetJumping(bool _jumping)
{
    this->jumping = _jumping;
}

bool Player::IsJumping() const
{
    return this->jumping;
}

void Player::Move(float gravity, float friction, float maxFallSpeed, float maxMoveSpeed, float minMoveSpeed)
{
    this->vy -= gravity;

    this->vy = fmaxf(this->vy, -maxFallSpeed);
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
    auto* playerBounds = this->boundingBox;
    if (playerBounds == nullptr)
        return;

    if (tile->HasTop())
    {
        float playerOldBottom = this->oldCY - playerBounds->GetHalfHeight();
        if (this->CollideTop(tile, playerBounds->Bottom(), playerOldBottom))
            return;
    }

    if (tile->HasLeft())
    {
        float playerOldRight = this->oldCX + playerBounds->GetHalfWidth();
        if (this->CollideLeft(tile, playerBounds->Right(), playerOldRight))
            return;
    }

    if (tile->HasRight())
    {
        float playerOldLeft = this->oldCX - playerBounds->GetHalfWidth();
        if (this->CollideRight(tile, playerBounds->Left(), playerOldLeft))
            return;
    }

    if (tile->HasBottom())
    {
        float playerOldTop = this->oldCY + playerBounds->GetHalfHeight();
        if (this->CollideBottom(tile, playerBounds->Top(), playerOldTop))
            return;
    }
}

bool Player::CollideTop(Tile* tile, float playerBottom, float playerOldBottom)
{
    auto* tileBounds = tile->GetBoundingBox();
    if (tileBounds == nullptr)
        return false;

    float platformTop = tileBounds->Top();
    if (playerBottom < platformTop && playerOldBottom >= platformTop)
    {
        tile->CollideTop(this);
        return true;
    }
    return false;
}

bool Player::CollideLeft(Tile* tile, float playerRight, float playerOldRight)
{
    auto* tileBounds = tile->GetBoundingBox();
    if (tileBounds == nullptr)
        return false;

    float platformLeft = tileBounds->Left();
    if (playerRight > platformLeft && playerOldRight <= platformLeft)
    {
        tile->CollideLeft(this);
        return true;
    }
    return false;
}

bool Player::CollideRight(Tile* tile, float playerLeft, float playerOldLeft)
{
    auto* tileBounds = tile->GetBoundingBox();
    if (tileBounds == nullptr)
        return false;

    float platformRight = tileBounds->Right();
    if (playerLeft < platformRight && playerOldLeft >= platformRight)
    {
        tile->CollideRight(this);
        return true;
    }
    return false;
}

bool Player::CollideBottom(Tile* tile, float playerTop, float playerOldTop)
{
    auto* tileBounds = tile->GetBoundingBox();
    if (tileBounds == nullptr)
        return false;

    float platformBottom = tileBounds->Bottom();
    if (playerTop > platformBottom && playerOldTop <= platformBottom)
    {
        tile->CollideBottom(this);
        return true;
    }
    return false;
}