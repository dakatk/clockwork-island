#ifndef ENGINE_TIMER_H__
#define ENGINE_TIMER_H__

#include <cstdint>

namespace engine
{
    // Courtesy of Lazy Foo' Productions:
    class Timer
    {
    private:
        uint32_t startTicks;
        uint32_t pausedTicks;

        bool paused;
        bool started;

    public:
        Timer();

        void Start();
        void Stop();
        void Pause();
        void UnPause();

        uint32_t Ticks() const;

        bool IsStarted() const;
        bool IsPaused() const;
    };
}

#endif /* ENGINE_TIMER_H__ */
