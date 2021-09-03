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

        bool CollideTop(Tile* tile, float playerBottom, float playerOldBottom);
        bool CollideLeft(Tile* tile, float playerRight, float playerOldRight);
        bool CollideRight(Tile* tile, float playerLeft, float playerOldLeft);
        bool CollideBottom(Tile* tile, float playerTop, float playerOldTop);

    public:
        Player(Texture* spritesheet, int x, int y, int width, int height);

        float GetVX() const;
        float GetVY() const;

        void SetVX(float vx);
        void SetVY(float vy);

        void ChangeVX(float dvx);
        void ChangeVY(float dvy);

        void SetJumping(bool jumping);
        bool IsJumping() const;

        void Move(float gravity, float friction, float maxJumpSpeed, float maxMoveSpeed, float minMoveSpeed);
        void MoveTo(int x, int y);

        void Collide(Tile* tile);
    };
}

#endif /* ENGINE_PLAYER_H__ */
