#ifndef CLOCKWORKISLAND_NEWENGINE_SPRING_H__
#define CLOCKWORKISLAND_NEWENGINE_SPRING_H__

#include "game/platforms/Platform.h"

namespace game
{
    namespace platforms
    {
        class Spring : public Platform
        {
        public:
            Spring(Texture* spritesheet, int rotation, int spriteClipX, int spriteClipY, uint8_t sides, int x, int y, int width, int height)
                : Platform(spritesheet, rotation, spriteClipX, spriteClipY, sides, x, y, width, height) {}

            void CollideTop(Sprite* entity) override;
            void SetBoundingBox(float boundsWidth, float boundsHeight) override;
            void Animate() override;
        };
    }
}

#endif //CLOCKWORKISLAND_NEWENGINE_SPRING_H__
