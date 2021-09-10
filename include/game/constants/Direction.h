#ifndef GAME_CONSTANTS_DIRECTION_H__
#define GAME_CONSTANTS_DIRECTION_H__

namespace game
{
    // TODO 'sleep' should be in milliseconds
    struct Direction
    {
        int value;
        int frames;
        int sleep;

        Direction(int value_, int frames_, int sleep_): value(value_), frames(frames_), sleep(sleep_) {}
    };

    namespace directions
    {
        const struct Direction STAND_LEFT(3, 8, 16); // NOLINT(cert-err58-cpp)
        const struct Direction STAND_RIGHT(2, 8, 16); // NOLINT(cert-err58-cpp)
        const struct Direction WALK_LEFT(1, 8, 3); // NOLINT(cert-err58-cpp)
        const struct Direction WALK_RIGHT(0, 8, 3); // NOLINT(cert-err58-cpp)
        const struct Direction JUMP_LEFT(5, 1, 0); // NOLINT(cert-err58-cpp)
        const struct Direction JUMP_RIGHT(4, 1, 0); // NOLINT(cert-err58-cpp)
    }
}

#endif /* GAME_CONSTANTS_DIRECTION_H__ */
