#include "engine/Viewport.h"
#include "engine/Window.h"

using namespace engine;

int Viewport::x;
int Viewport::y;

int Viewport::GetX()
{
    return x;
}

int Viewport::GetY()
{
    return y;
}

int Viewport::GetMaxX()
{
    return (int)Window::GetBufferWidth() * 2;
}

int Viewport::GetMaxY()
{
    return (int)Window::GetBufferHeight() * 2;
}

void Viewport::Constrain()
{
    if (x < 0) x = 0;

    else if (x >= Viewport::GetMaxX())
        x = Viewport::GetMaxX();

    if (y < 0) y = 0;

    else if (y >= Viewport::GetMaxX())
        y = Viewport::GetMaxY();
}

void Viewport::SnapTo(float centerX, float centerY)
{
    x = (int)(centerX - ((float)Window::GetBufferWidth() / 2.0f));
    y = (int)(centerY - ((float)Window::GetBufferHeight() / 2.0f));
}