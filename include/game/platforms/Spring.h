#ifndef GAME_PLATFORMS_SPRING_H__
#define GAME_PLATFORMS_SPRING_H__

#include <engine/Timer.h>
#include "game/platforms/Platform.h"

namespace game
{
    namespace platforms
    {
        class Spring : public Platform
        {
        private:
            Timer animTimer;
            int animDirection;
            uint32_t animWait;
            bool activated;

        public:
            Spring(Texture* spritesheet, int rotation, uint8_t sides, int x, int y, int width, int height);

            void CollideTop(Sprite* entity) override;
            void SetBoundingBox(float boundsWidth, float boundsHeight) override;
            void Animate() override;
        };
    }
}

#endif /* GAME_PLATFORMS_SPRING_H__ */
