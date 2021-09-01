#ifndef CLOCKWORKISLAND_NEWENGINE_SPRING_H__
#define CLOCKWORKISLAND_NEWENGINE_SPRING_H__

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
            bool activated;
            int animDirection;
            uint32_t animWait;

        public:
            Spring(Texture* spritesheet, int rotation, uint8_t sides, int x, int y, int width, int height);

            void CollideTop(Sprite* entity) override;
            void SetBoundingBox(float boundsWidth, float boundsHeight) override;
            void Animate() override;
        };
    }
}

#endif //CLOCKWORKISLAND_NEWENGINE_SPRING_H__
