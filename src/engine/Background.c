#include "engine/Background.h"
#include "engine/Viewport.h"
#include "engine/Buffer.h"

#include <stdio.h>

void Background_Init(struct Background* background, struct Bitmap layer0, struct Bitmap layer1)
{
	background->layer0 = layer0;
	background->layer1 = layer1;
}

// TODO FUTURE Parallax scrolling (maybe add a third layer?)

void Background_Render(struct Background* background)
{
    Buffer_BlitBitmapFull(&background->layer0);
    Buffer_BlitBitmapFull(&background->layer1);
}

void Background_Destroy(struct Background* background)
{
    Bitmap_Destroy(&background->layer0);
    Bitmap_Destroy(&background->layer1);
}
