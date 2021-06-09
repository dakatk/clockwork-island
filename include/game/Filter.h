#ifndef CLOCKWORKISLAND_FILTER_H__
#define CLOCKWORKISLAND_FILTER_H__

#include <cstdint>

#define NUM_FILTERS 6
#define FILTER_ALPHA 55

namespace game
{
    class Filter
    {
    private:
        uint8_t r;
        uint8_t g;
        uint8_t b;

    public:
        Filter(uint8_t r_, uint8_t g_, uint8_t b_);

        uint8_t GetR() const;
        uint8_t GetG() const;
        uint8_t GetB() const;
    };

    namespace filters
    {
        const Filter RED(255, 0, 0);
        const Filter GREEN(0, 255, 0);
        const Filter BLUE(0, 0, 255);
        const Filter ORANGE(255, 175, 0);
        const Filter VIOLET(255, 0, 221);
    }
}

#endif /* CLOCKWORKISLAND_FILTER_H__ */
