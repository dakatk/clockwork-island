#include "game/platforms/Spring.h"

using namespace game;
using namespace platforms;

void Spring::CollideTop(Sprite* entity)
{
    Platform::CollideTop(entity);
    // TODO Bounce player
    // TODO Animate spring
    /*
     * Spring should animate between three frames (see sprite sheet)
     * It should go forward in frame-count when the player is being launched,
     * And then backwards after a short delay. The hitbox should change only on
     * the third frame of animation, allowing the player to be launched successfully
     * without any collision issues. Laslty, being launched by the Spring needs
     * to ensure that the player has no control over their y-velocity (jump button disabled)
     */
}

void Spring::SetBoundingBox(float boundsWidth, float boundsHeight)
{
    float halfWidth = boundsWidth / 2.0f;
    float halfHeight = boundsHeight / 2.0f;

    float centerX = (float)this->x + ((float)this->width / 2.0f);
    float centerY = (float)this->y - ((float)this->height - halfHeight);

    this->boundingBox = new BoundingBox(centerX, centerY, halfWidth, halfHeight);
}