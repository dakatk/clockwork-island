#ifndef CLOCKWORKISLAND_ROBOT_H__
#define CLOCKWORKISLAND_ROBOT_H__

#include "engine/Player.h"
#include "Direction.h"

using namespace engine;

namespace game
{
    class Robot : public Player
    {
    private:
        const Direction* direction;

        uint8_t activeFilter;
        uint8_t allowedFilters;

        int ticks;

    public:
        Robot(Texture* spritesheet, int x, int y, uint8_t allowedFilters);

        uint8_t GetAllowedFilters() const;
        uint8_t GetActiveFilter() const;

        void IncFilter();
        void DecFilter();
        void SetFilter(uint8_t activeFilter);

        void UpdateDirection();
        void Animate();

        void Render() override;
    };
}

#endif /* CLOCKWORKISLAND_ROBOT_H__ */
