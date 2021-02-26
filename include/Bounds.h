#ifndef GAME_BOUNDS_H__
#define GAME_BOUNDS_H__

enum InterAt {
	INTER_AT_NONE = -1,
	INTER_AT_TOP = 0,
	INTER_AT_LEFT = 1,
	INTER_AT_BOTTOM = 2,
	INTER_AT_RIGHT = 3
};

enum InterFrom {
	INTER_FROM_NONE = -1,
	INTER_FROM_TOP_LEFT = 0,
	INTER_FROM_TOP_RIGHT = 1,
	INTER_FROM_BOTTOM_LEFT = 2,
	INTER_FROM_BOTTOM_RIGHT = 3
};

struct RayHit {
	enum InterAt intersectAt;
	enum InterFrom intersectFrom;

	float intersectX;
	float intersectY;
	float delta;
};

// TODO FUTURE We could make this a sequence of lines for more
// abstraction/customizibility
struct Bounds {
	float x;
	float y;
	int w;
	int h;
};

struct RayHit Bounds_Intersect(struct Bounds* a, struct Bounds* b, float avx, float avy);

#endif /* GAME_BOUNDS_H__ */
