#ifndef GAME_HAZARD_H__
#define GAME_HAZARD_H__

#include "engine/Sprite.h"

namespace game
{
    using namespace engine;

    class Hazard
    {
    public:
        virtual ~Hazard() = default;
        virtual void Effect(Sprite* sprite) = 0;
        virtual bool IsApplicable(uint8_t filter) = 0;
    };
}

#endif /* GAME_HAZARD_H__ */
