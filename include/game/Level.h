#ifndef CLOCKWORKISLAND_LEVEL_H__
#define CLOCKWORKISLAND_LEVEL_H__

#include "engine/Background.h"
#include "Robot.h"
#include "platforms/Platform.h"

namespace game
{
    using namespace platforms;

    class Level
    {
    private:
        struct PlatformNode
        {
            Platform* platform;
            struct PlatformNode* next;
        };

        struct PlatformNode* head;
        Background* background;

    public:
        explicit Level(Background* background);
        ~Level();

        void AddPlatform(Platform* platform);
        void CheckPhysics(Robot& player);
        void ScrollBackground(Robot& player);

        void Render(uint8_t activeFilter);
    };
}

#endif /* CLOCKWORKISLAND_LEVEL_H__ */
