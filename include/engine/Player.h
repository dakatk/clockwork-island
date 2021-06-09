#ifndef ENGINE_PLAYER_H__
#define ENGINE_PLAYER_H__

#include "engine/Texture.h"
#include "engine/BoundingBox.h"
#include "engine/Sprite.h"
#include "engine/Tile.h"

namespace engine
{
    class Player : public Sprite
    {
    private:
        bool jumping;

        float oldCX;
        float oldCY;

        float vx;
        float vy;

        bool CollideTop(float platformTop, float playerBottom, float playerOldBottom);
        bool CollideLeft(float platformLeft, float playerRight, float playerOldRight);
        bool CollideRight(float platformRight, float playerLeft, float playerOldLeft);
        bool CollideBottom(float platformBottom, float playerTop, float playerOldTop);

    public:
        Player(Texture* spritesheet, int x, int y, int width, int height);

        float GetVX() const;
        float GetVY() const;

        void ChangeVX(float dvx);
        void ChangeVY(float dvy);

        void SetJumping();
        bool IsJumping() const;

        void Move(float gravity, float friction, float maxJumpSpeed, float maxMoveSpeed, float minMoveSpeed);

        void Collide(Tile *tile);
    };
}

#endif /* ENGINE_PLAYER_H__ */
