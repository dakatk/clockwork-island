#include "Filter.h"
#include "Buffer.h"

#define FILTER_ALPHA 55

const struct Filter Filter_RED = {.r=255, .g=0, .b=0};
const struct Filter Filter_GREEN = {.r=0, .g=255, .b=0};
const struct Filter Filter_BLUE = {.r=0, .g=0, .b=255};
const struct Filter Filter_ORANGE = {.r=255, .g=175, .b=0};
const struct Filter Filter_VIOLET = {.r=255, .g=0, .b=221};

void Filter_Render(const struct Filter* filter, SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, filter->r, filter->g,filter->b, FILTER_ALPHA);
    SDL_Rect screenBounds = {
            .x = 0,
            .y = 0,
            .w = BUFFER_WIDTH,
            .h = BUFFER_HEIGHT
    };
    SDL_RenderFillRect(renderer, &screenBounds);
}