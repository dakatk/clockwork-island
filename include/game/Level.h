#ifndef GAME_LEVEL_H__
#define GAME_LEVEL_H__

#include "util/LinkedList.h"
#include "engine/Background.h"
#include "game/Hazard.h"
#include "game/Robot.h"
#include "game/platforms/Platform.h"

namespace game
{
    using namespace platforms;
    using namespace util;

    class Level
    {
    private:
        LinkedList<Platform> platforms;
        LinkedList<Hazard> hazards;
        Background* background;

    public:
        explicit Level(Background* background);
        ~Level();

        void AddPlatform(Platform* platform);
        void AddHazard(Hazard* hazard);

        void CheckPhysics(Robot& player);
        void ScrollBackground(Robot& player);

        void Render(uint8_t activeFilter);
    };
}

#endif /* GAME_LEVEL_H__ */
