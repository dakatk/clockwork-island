#ifndef GAME_PLATFORMS_PLATFORM_H__
#define GAME_PLATFORMS_PLATFORM_H__

#include "engine/Tile.h"

using namespace engine;

namespace game
{
    namespace platforms
    {
        class Platform : public Tile
        {
        private:
            uint8_t visible;

        public:
            Platform(Texture* spritesheet, int rotation, int spriteClipX, int spriteClipY, uint8_t sides, int x, int y, int width, int height);

            void SetVisibility(uint8_t visible);
            bool IsVisible(uint8_t filter) const;

            void CollideTop(Sprite* entity) override;
            void CollideBottom(Sprite* entity) override;
            void CollideLeft(Sprite* entity) override;
            void CollideRight(Sprite* entity) override;

            void Animate() override {}
        };
    }
}

#endif /* GAME_PLATFORMS_PLATFORM_H__ */