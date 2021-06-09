#ifndef ENGINE_TILE_H__
#define ENGINE_TILE_H__

#include "engine/BoundingBox.h"
#include "engine/Texture.h"
#include "engine/Sprite.h"

namespace engine
{
    class Tile : public Sprite
    {
    private:
        // Encoding = Left | Bottom | Right | Top
        uint8_t sides;

    public:
        Tile(Texture *spritesheet, int angle, int spriteClipX, int spriteClipY, uint8_t sides, int x, int y, int width,
             int height);

        bool HasTop() const;
        bool HasLeft() const;
        bool HasRight() const;
        bool HasBottom() const;

        bool IsOffscreen();
    };
}

#endif /* ENGINE_TILE_H__ */
