#ifndef CLOCKWORKISLAND_VIEWPORT_H__
#define CLOCKWORKISLAND_VIEWPORT_H__

#include "Bool.h"

// Leave space for one extra viewport, since the viewport
// is moved from the bottom-left corner
#define VIEWPORT_MAX_X 1200 // Levels are three viewports wide...
#define VIEWPORT_MAX_Y 1800 // and three viewports tall

extern int Viewport_X;
extern int Viewport_Y;

void Viewport_Constrain();
void Viewport_SnapTo(float centerX, float centerY);

#endif /* CLOCKWORKISLAND_VIEWPORT_H__ */
