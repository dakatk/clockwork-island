#include "engine/Direction.h"

const struct Direction Direction_STAND_LEFT = {.value=3, .frames=8, .sleep=16};
const struct Direction Direction_STAND_RIGHT = {.value=2, .frames=8, .sleep=16};
const struct Direction Direction_WALK_LEFT = {.value=1, .frames=8, .sleep=3};
const struct Direction Direction_WALK_RIGHT = {.value=0, .frames=8, .sleep=3};
const struct Direction Direction_JUMP_LEFT = {.value=5, .frames=1, .sleep=0};
const struct Direction Direction_JUMP_RIGHT = {.value=4, .frames=1, .sleep=0};
