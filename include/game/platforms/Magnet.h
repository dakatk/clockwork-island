#ifndef GAME_PLATFORMS_MAGNET_H
#define GAME_PLATFORMS_MAGNET_H

#include "game/platforms/Platform.h"
#include "engine/Timer.h"
#include "game/Hazard.h"

namespace game
{
    namespace platforms
    {
        class Magnet : public Platform, public Hazard
        {
        private:
            Timer animTimer;
            BoundingBox field;

        public:
            Magnet(Texture* spritesheet, int rotation, uint8_t sides, int x, int y, int width, int height);

            void Effect(Sprite* sprite) override;
            bool IsApplicable(uint8_t filter) override;
            void Animate() override;
        };
    }
}

#endif /* GAME_PLATFORMS_MAGNET_H */
