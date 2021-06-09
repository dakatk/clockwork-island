#include "engine/BoundingBox.h"
#include <cmath>

using namespace engine;

BoundingBox::BoundingBox(float centerX, float centerY, float halfWidth, float halfHeight)
{
    this->centerX = centerX;
    this->centerY = centerY;
    this->halfWidth = halfWidth;
    this->halfHeight = halfHeight;
}

float BoundingBox::GetCenterX() const
{
    return this->centerX;
}

float BoundingBox::GetCenterY() const
{
    return this->centerY;
}

void BoundingBox::SetCenterX(float centerX_)
{
    this->centerX = centerX_;
}

void BoundingBox::SetCenterY(float centerY_)
{
    this->centerY = centerY_;
}

float BoundingBox::GetHalfWidth() const
{
    return this->halfWidth;
}

float BoundingBox::GetHalfHeight() const
{
    return this->halfHeight;
}

float BoundingBox::Top() const
{
    return this->centerY + this->halfHeight;
}

float BoundingBox::Left() const
{
    return this->centerX - this->halfWidth;
}

float BoundingBox::Right() const
{
    return this->centerX + this->halfWidth;
}

float BoundingBox::Bottom() const
{
    return this->centerY - this->halfHeight;
}

void BoundingBox::Move(float dx, float dy)
{
    this->centerX += dx;
    this->centerY += dy;
}

bool BoundingBox::Intersects(BoundingBox* other) const
{
    if (other == nullptr)
        return false;

    float xDiff = fabsf(this->centerX - other->centerX);
    float yDiff = fabsf(this->centerY - other->centerY);

    return xDiff < (this->halfWidth + other->halfWidth) &&
           yDiff < (this->halfHeight + other->halfHeight);
}

