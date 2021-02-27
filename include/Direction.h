#ifndef CLOCKWORKISLAND_DIRECTION_H__
#define CLOCKWORKISLAND_DIRECTION_H__

struct Direction {
	int value;
	int frames;
	int sleep;
};

extern const struct Direction Direction_STAND_LEFT;
extern const struct Direction Direction_STAND_RIGHT;
extern const struct Direction Direction_WALK_LEFT;
extern const struct Direction Direction_WALK_RIGHT;
extern const struct Direction Direction_JUMP_LEFT;
extern const struct Direction Direction_JUMP_RIGHT;

#endif /* CLOCKWORKISLAND_DIRECTION_H__ */
