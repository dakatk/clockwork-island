#ifndef ENGINE_TIMER_H__
#define ENGINE_TIMER_H__

#include <cstdint>

namespace engine
{
    class Timer
    {
    private:
        uint32_t startTicks;
        bool started;

    public:
        Timer();

        void Start();
        uint32_t Ticks() const;
    };
}

#endif /* ENGINE_TIMER_H__ */
