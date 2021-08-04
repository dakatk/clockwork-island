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
        const struct Direction* direction;
        int ticks;

        uint8_t activeFilter;
        uint8_t allowedFilters;

    public:
        explicit Robot(Texture* spritesheet);

        uint8_t GetAllowedFilters() const;
        void SetAllowedFilters(uint8_t allowedFilters_);

        uint8_t GetActiveFilter() const;
        void SetActiveFilter(uint8_t activeFilter_);

        void IncFilter();
        void DecFilter();

        void UpdateDirection();
        void Animate();

        void Render() override;
    };
}

#endif /* CLOCKWORKISLAND_ROBOT_H__ */
