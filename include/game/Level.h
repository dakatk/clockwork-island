#ifndef CLOCKWORKISLAND_LEVEL_H__
#define CLOCKWORKISLAND_LEVEL_H__

#include "Robot.h"
#include "Platform.h"

namespace game
{
    class Level
    {
    private:
        struct PlatformNode
        {
            Platform* platform;
            struct PlatformNode* next;
        };
        struct PlatformNode* head;

        Robot* player;

    public:
        Level();
        ~Level();

        void AddPlatform(Platform* platform);
        void CheckPhysics(Robot* player);

        void Render(uint8_t activeFilter);
    };
}

#endif /* CLOCKWORKISLAND_LEVEL_H__ */
