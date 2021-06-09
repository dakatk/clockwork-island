#ifndef CLOCKWORKISLAND_PLATFORM_H__
#define CLOCKWORKISLAND_PLATFORM_H__

#include "engine/Tile.h"

using namespace engine;

namespace game
{
    class Platform : public Tile
    {
    private:
        uint8_t visible;

    public:
        Platform(Texture* spritesheet, int angle, int spriteClipX, int spriteClipY, uint8_t sides, int x, int y, int width, int height);

        void SetVisibility(uint8_t visible);
        bool IsVisible(uint8_t filter) const;
    };
}

#endif /* CLOCKWORKISLAND_PLATFORM_H__ */