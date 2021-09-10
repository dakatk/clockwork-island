#ifndef GAME_CONSTANTS_FILTER_H__
#define GAME_CONSTANTS_FILTER_H__

#include <cstdint>

#define NUM_FILTERS 3
#define FILTER_ALPHA 30

namespace game
{
    struct Filter
    {
        uint8_t r;
        uint8_t g;
        uint8_t b;

        Filter(uint8_t r_, uint8_t g_, uint8_t b_): r(r_), g(g_), b(b_) {}
    };

    namespace filters
    {
        const struct Filter PAST(255, 175, 0); // NOLINT(cert-err58-cpp
        const struct Filter FUTURE(0, 0, 255); // NOLINT(cert-err58-cpp)
    }
}

#endif /* GAME_CONSTANTS_FILTER_H__ */