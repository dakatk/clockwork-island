#include "Bounds.h"
#include "Bool.h"

// TODO Physical interactions need an overhaul. start here...

struct Line {
	float x0, y0;
	float x1, y1;
};

static void RayCast(struct RayHit* hit, struct Line* ray, struct Line* line, enum InterFrom interFrom, enum InterAt interAt);
static bool IntersectFails(struct Bounds* a, struct Bounds* b, float avx, float avy);

// Order matters, assume 'a' is moving and attempting to intersect 'b'
struct RayHit Bounds_Intersect(struct Bounds* a, struct Bounds* b, float avx, float avy)
{
	struct RayHit hit = {
		.intersectAt = INTER_AT_NONE,
		.intersectFrom = INTER_FROM_NONE,
		.intersectX = -1.0f,
		.intersectY = -1.0f,
		.delta = -1.0f
	};

	if (IntersectFails(a, b, avx, avy)) 
		return hit;

	// 'b' line extractions:
	struct Line bTop = {
		.x0 = b->x,
		.y0 = b->y,
		.x1 = b->x + (float)b->w,
		.y1 = b->y
	};

	struct Line bLeft = {
		.x0 = b->x,
		.y0 = b->y,
		.x1 = b->x,
		.y1 = b->y + (float)b->h
	};

	struct Line bBottom = {
		.x0 = b->x,
		.y0 = b->y + (float)b->h,
		.x1 = b->x + (float)b->w,
		.y1 = b->y + (float)b->h
	};

	struct Line bRight = {
		.x0 = b->x + (float)b->w,
		.y0 = b->y,
		.x1 = b->x + (float)b->w,
		.y1 = b->y + (float)b->h
	};

	// 'a' line extractions:
	struct Line aTopLeft = {
		.x0 = a->x,
		.y0 = a->y,
		.x1 = a->x + avx,
		.y1 = a->y + avy,
	};

	struct Line aTopRight = {
		.x0 = a->x + (float)a->w,
		.y0 = a->y,
		.x1 = a->x + (float)a->w + avx,
		.y1 = a->y + avy
	};

	struct Line aBottomLeft = {
		.x0 = a->x,
		.y0 = a->y + (float)a->h,
		.x1 = a->x + avx,
		.y1 = a->y + (float)a->h + avy,
	};

	struct Line aBottomRight = {
		.x0 = a->x + (float)a->w,
		.y0 = a->y + (float)a->h,
		.x1 = a->x + (float)a->w + avx,
		.y1 = a->y + (float)a->h + avy
	};

	// TODO FUTURE There must be a better way to do this...
	RayCast(&hit, &aTopLeft, &bTop, INTER_FROM_TOP_LEFT, INTER_AT_TOP);
	RayCast(&hit, &aTopLeft, &bLeft, INTER_FROM_TOP_LEFT, INTER_AT_LEFT);
	RayCast(&hit, &aTopLeft, &bBottom, INTER_FROM_TOP_LEFT, INTER_AT_BOTTOM);
	RayCast(&hit, &aTopLeft, &bRight, INTER_FROM_TOP_LEFT, INTER_AT_RIGHT);

	RayCast(&hit, &aTopRight, &bTop, INTER_FROM_TOP_RIGHT, INTER_AT_TOP);
	RayCast(&hit, &aTopRight, &bLeft, INTER_FROM_TOP_RIGHT, INTER_AT_LEFT);
	RayCast(&hit, &aTopRight, &bBottom, INTER_FROM_TOP_RIGHT, INTER_AT_BOTTOM);
	RayCast(&hit, &aTopRight, &bRight, INTER_FROM_TOP_RIGHT, INTER_AT_RIGHT);

	RayCast(&hit, &aBottomLeft, &bTop, INTER_FROM_BOTTOM_LEFT, INTER_AT_TOP);
	RayCast(&hit, &aBottomLeft, &bLeft, INTER_FROM_BOTTOM_LEFT, INTER_AT_LEFT);
	RayCast(&hit, &aBottomLeft, &bBottom, INTER_FROM_BOTTOM_LEFT, INTER_AT_BOTTOM);
	RayCast(&hit, &aBottomLeft, &bRight, INTER_FROM_BOTTOM_LEFT, INTER_AT_RIGHT);

	RayCast(&hit, &aBottomRight, &bTop, INTER_FROM_BOTTOM_RIGHT, INTER_AT_TOP);
	RayCast(&hit, &aBottomRight, &bLeft, INTER_FROM_BOTTOM_RIGHT, INTER_AT_LEFT);
	RayCast(&hit, &aBottomRight, &bBottom, INTER_FROM_BOTTOM_RIGHT, INTER_AT_BOTTOM);
	RayCast(&hit, &aBottomRight, &bRight, INTER_FROM_BOTTOM_RIGHT, INTER_AT_RIGHT);

	return hit;
}

static inline bool VerticalLine(struct Line* line)
{
	return line->x0 == line->x1;
}

static bool MatchingSlopes(float adx, float ady, float bdx, float bdy)
{
	if (adx == 0.0f && bdx == 0.0f)
		return true;
	
	else if (ady == 0.0f && bdy == 0.0f) 
		return true;

	float slopeA = ady / adx;
	float slopeB = bdy / bdx;

	return slopeA == slopeB;
}

// Determine point where lines intersect
static bool LineIntersectionPoint(struct Line* a, struct Line* b, float* intersectX, float* intersectY)
{
	float adx = a->x1 - a->x0;
	float ady = a->y1 - a->y0;
	float bdx = b->x1 - b->x0;
	float bdy = b->y1 - b->y0;

	float slopeA, slopeB;
	float interceptA, interceptB;

	// Special case for parallel lines
	if (MatchingSlopes(adx, ady, bdx, bdy)) 
		return false;
	
	// Special case for if 'a' is vertical (infinite slope)
	else if (VerticalLine(a))
	{
		slopeB = bdy / bdx;
		interceptB = (-slopeB * b->x1) + b->y1;

		*intersectX = a->x0;
		*intersectY = slopeB * (*intersectX) + interceptB;
	}
	// Special case for if 'b' is vertical (infinite slope)
	else if (VerticalLine(b))
	{
		slopeA = ady / adx;
		interceptA = (-slopeA * a->x1) + a->y1;

		*intersectX = b->x0;
		*intersectY = slopeA * (*intersectX) + interceptA;
	}
	else 
	{
		slopeA = ady / adx;
		slopeB = bdy / bdx;

		interceptA = (-slopeA * a->x1) + a->y1;
		interceptB = (-slopeB * b->x1) + b->y1;

		*intersectX = (interceptB - interceptA) / (slopeA - slopeB);
		*intersectY = slopeA * (*intersectX) + interceptA;
	}
	return true;
}

static void RayCast(struct RayHit* hit, struct Line* ray, struct Line* line, enum InterFrom interFrom, enum InterAt interAt)
{
	float intersectX = 0.0f;
	float intersectY = 0.0f;

	if (!LineIntersectionPoint(ray, line, &intersectX, &intersectY))
		return;

	float deltaX = intersectX - ray->x0;
	float deltaY = intersectY - ray->y0;
	float delta = (deltaX * deltaX) + (deltaY * deltaY);

	bool updateHit = delta < hit->delta;

	if (hit->intersectAt == INTER_AT_NONE || hit->intersectFrom == INTER_FROM_NONE || updateHit)
	{
		hit->intersectAt = interAt;
		hit->intersectFrom = interFrom;
		hit->intersectX = intersectX;
		hit->intersectY = intersectY;
		hit->delta = delta;
	}
}

static bool IntersectFails(struct Bounds* a, struct Bounds* b, float avx, float avy)
{
	// 'a' is to the left of 'b'
	if ((a->x + (float)a->w + avx) < b->x)
		return true;

	// 'b' is to the left of 'a'
	else if ((b->x + (float)b->w) < (a->x + avx))
		return true;

	// 'a' is above 'b'
	if ((a->y + (float)a->h + avy) < b->y)
		return true;

	// 'b' is above 'a'
	else if ((b->y + (float)b->h) < (a->y + avy))
		return true;

	return false;
}