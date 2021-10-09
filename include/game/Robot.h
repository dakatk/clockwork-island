#ifndef GAME_ROBOT_H__
#define GAME_ROBOT_H__

#include "engine/Player.h"
#include "constants/Direction.h"
#include "engine/Timer.h"

using namespace engine;

namespace game
{
    class Robot : public Player
    {
    private:
        const struct Direction* direction;
        Timer timer;

        uint8_t activeFilter;
        uint8_t allowedFilters;

        bool wasJumping;

    public:
        explicit Robot(Texture* spritesheet);

        uint8_t GetAllowedFilters() const;
        void SetAllowedFilters(uint8_t allowedFilters_);

        uint8_t GetActiveFilter() const;
        void SetActiveFilter(uint8_t activeFilter_);

        void UpdateDirection();
        
        void Animate() override;
        void Render() override;
    };
}

#endif /* GAME_ROBOT_H__ */
