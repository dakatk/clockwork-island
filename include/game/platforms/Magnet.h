#ifndef CLOCKWORKISLAND_NEWENGINE_MAGNET_H
#define CLOCKWORKISLAND_NEWENGINE_MAGNET_H

#include "game/platforms/Platform.h"
#include "engine/Timer.h"

namespace game
{
    namespace platforms
    {
        class Magnet : public Platform
        {
        private:
            Timer animTimer;

        public:
            Magnet(Texture* spritesheet, int rotation, uint8_t sides, int x, int y, int width, int height);

            void Animate() override;
        };
    }
}

#endif //CLOCKWORKISLAND_NEWENGINE_MAGNET_H
