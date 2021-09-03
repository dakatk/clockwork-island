#ifndef ENGINE_SPRITE_H__
#define ENGINE_SPRITE_H__

#include "engine/Texture.h"
#include "engine/BoundingBox.h"

namespace engine
{
    class Sprite
    {
    protected:
        Texture* spritesheet;
        BoundingBox* boundingBox;

        float x;
        float y;

        int width;
        int height;

        int spriteClipX;
        int spriteClipY;

        int rotation;

    public:
        Sprite(Texture* spritesheet, float x, float y, int width, int height);
        virtual ~Sprite();

        void SetY(float y_) { this->y = y_; }

        virtual void SetBoundingBox(float boundsWidth, float boundsHeight);
        BoundingBox* GetBoundingBox();

        virtual void Render();
        virtual void Animate() = 0;
    };
}

#endif /* ENGINE_SPRITE_H__ */
