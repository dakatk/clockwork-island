#ifndef CLOCKWORKISLAND_FILTER_H__
#define CLOCKWORKISLAND_FILTER_H__

#include <cstdint>

#define NUM_FILTERS 6
#define FILTER_ALPHA 55

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
        const struct Filter RED(255, 0, 0); // NOLINT(cert-err58-cpp)
        const struct Filter GREEN(0, 255, 0); // NOLINT(cert-err58-cpp)
        const struct Filter BLUE(0, 0, 255); // NOLINT(cert-err58-cpp)
        const struct Filter ORANGE(255, 175, 0); // NOLINT(cert-err58-cpp)
        const struct Filter VIOLET(255, 0, 221); // NOLINT(cert-err58-cpp)
    }
}

#endif /* CLOCKWORKISLAND_FILTER_H__ */