#ifndef GAME_VIEWPORT_H__
#define GAME_VIEWPORT_H__

#include "Bool.h"

// Treat everything as if the display is 800x600,
// scale the graphics when rendering
#define VIEWPORT_WIDTH 800
#define VIEWPORT_HEIGHT 600

// Leave space for one extra viewport, since the viewport
// is moved from the bottom-left corner
#define VIEWPORT_MAX_X 1200 // Levels are three viewports wide...
#define VIEWPORT_MAX_Y 1800 // and three viewports tall

extern int Viewport_X;
extern int Viewport_Y;

void Viewport_Constrain();
void Viewport_SnapTo(float centerX, float centerY);

#endif /* GAME_VIEWPORT_H__ */
