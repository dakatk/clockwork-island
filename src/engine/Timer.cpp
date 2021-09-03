#include "engine/Timer.h"
#include <SDL.h>

using namespace engine;

Timer::Timer()
{
    this->startTicks = 0;
    this->started = false;
}

void Timer::Start()
{
    this->startTicks = SDL_GetTicks();
    this->started = true;
}

uint32_t Timer::Ticks() const
{
    uint32_t time = 0;

    if (this->started)
        time = SDL_GetTicks() - this->startTicks;

    return time;
}
