#include "Direction.h"

Direction::Direction(int value_, int frames_, int sleep_)
{
    value = value_;
    frames = frames_;
    sleep = sleep_;
}

int Direction::GetValue() const
{
    return value;
}

int Direction::GetFrames() const
{
    return frames;
}

int Direction::GetSleep() const
{
    return sleep;
}