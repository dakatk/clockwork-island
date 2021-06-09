#include "Filter.h"

Filter::Filter(uint8_t r_, uint8_t g_, uint8_t b_)
{
    r = r_;
    g = g_;
    b = b_;
}

uint8_t Filter::GetR() const
{
    return r;
}

uint8_t Filter::GetG() const
{
    return g;
}

uint8_t Filter::GetB() const
{
    return b;
}