#include "Viewport.h"

int Viewport_X = 0;
int Viewport_Y = 0;

void Viewport_Constrain()
{
	if (Viewport_X < 0)
		Viewport_X = 0;

	else if (Viewport_X >= VIEWPORT_MAX_X)
		Viewport_X = VIEWPORT_MAX_X;

	if (Viewport_Y < 0)
		Viewport_Y = 0;
		
	else if (Viewport_Y >= VIEWPORT_MAX_Y)
		Viewport_Y = VIEWPORT_MAX_Y;
}

void Viewport_SnapTo(float centerX, float centerY) 
{
	Viewport_X = (int)(centerX - (VIEWPORT_WIDTH / 2.0f));
	Viewport_Y = (int)(centerY - (VIEWPORT_HEIGHT / 2.0f));
}