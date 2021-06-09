#include "engine/Timer.h"
#include <SDL.h>

using namespace engine;

Timer::Timer()
{
    this->startTicks = 0;
    this->pausedTicks = 0;

    this->started = false;
    this->paused = false;
}

void Timer::Start()
{
    this->started = true;
    this->paused = false;

    this->startTicks = SDL_GetTicks();
    this->pausedTicks = 0;
}

void Timer::Stop()
{
    this->started = false;
    this->paused = false;

    this->startTicks = 0;
    this->pausedTicks = 0;
}

void Timer::Pause()
{
    if (this->started && !this->paused)
    {
        this->paused = true;

        this->pausedTicks = SDL_GetTicks() - this->startTicks;
        this->startTicks = 0;
    }
}

void Timer::UnPause()
{
    if (this->started && this->paused)
    {
        this->paused = false;

        this->startTicks = SDL_GetTicks() - this->pausedTicks;
        this->pausedTicks = 0;
    }
}

uint32_t Timer::Ticks() const
{
    uint32_t time = 0;

    if (this->started)
    {
        if (this->paused)
            time = this->pausedTicks;
        else
            time = SDL_GetTicks() - this->startTicks;
    }
    return time;
}

bool Timer::IsStarted() const
{
    return this->started;
}

bool Timer::IsPaused() const
{
    return this->started && this->paused;
}