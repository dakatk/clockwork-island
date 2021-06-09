#ifndef CLOCKWORKISLAND_DIRECTION_H__
#define CLOCKWORKISLAND_DIRECTION_H__

class Direction {
private:
    int value;
    int frames;
    int sleep;

public:
    Direction(int value_, int frames_, int sleep_);

    int GetValue() const;
    int GetFrames() const;
    int GetSleep() const;
};

namespace directions
{
    const Direction STAND_LEFT(3, 8, 16);
    const Direction STAND_RIGHT(2, 8, 16);
    const Direction WALK_LEFT(1, 8, 3);
    const Direction WALK_RIGHT(0, 8, 3);
    const Direction JUMP_LEFT(5, 1, 0);
    const Direction JUMP_RIGHT(4, 1, 0);
}

#endif /* CLOCKWORKISLAND_DIRECTION_H__ */
