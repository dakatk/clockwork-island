#ifndef CLOCKWORKISLAND_VIEWPORT_H__
#define CLOCKWORKISLAND_VIEWPORT_H__

#include "Bool.h"

#define VIEWPORT_MAX_X 1200
#define VIEWPORT_MAX_Y 1800

extern int Viewport_X;
extern int Viewport_Y;

void Viewport_Constrain();
void Viewport_SnapTo(float centerX, float centerY);

#endif /* CLOCKWORKISLAND_VIEWPORT_H__ */
