#include "engine/Background.h"
#include "engine/Window.h"
#include "engine/Viewport.h"

using namespace engine;

static const float LAYER_SCALES[BACKGROUND_NUM_LAYERS] = {
        1.0f, 0.85f, 0.75f
};

Background::Background(std::string filenames[BACKGROUND_NUM_LAYERS])
{
    int texWidth, texHeight;
    int clipWidth, clipHeight;

    for (int i = 0; i < BACKGROUND_NUM_LAYERS; i ++)
    {
        if (filenames[i].empty())
        {
            layers[i].texture = nullptr;
            continue;
        }

        clipWidth = (int)((float)Window::GetBufferWidth() * LAYER_SCALES[i]);
        clipHeight = (int)((float)Window::GetBufferHeight() * LAYER_SCALES[i]);

        this->layers[i].texture = new Texture(filenames[i], clipWidth, clipHeight);
        this->layers[i].texture->QueryBitmapDims(&texWidth, &texHeight);

        this->layers[i].maxScrollX = texWidth - clipWidth;
        this->layers[i].maxScrollY = texHeight - clipHeight;
    }
}

Background::~Background()
{
    for (auto& layer : this->layers)
        delete layer.texture;
}

void Background::Scroll()
{
    for (auto& layer : this->layers)
    {
        if (layer.texture == nullptr)
            continue;

        int viewportFlippedY = Viewport::GetMaxY() - Viewport::GetY();

        int clipX = (Viewport::GetX() * layer.maxScrollX) / Viewport::GetMaxX();
        int clipY = (viewportFlippedY * layer.maxScrollY) / Viewport::GetMaxY();

        layer.texture->GetClip()->x = clipX;
        layer.texture->GetClip()->y = clipY;
    }
}

void Background::Render()
{
    for (auto& layer : this->layers)
    {
        if (layer.texture == nullptr)
            continue;

        Window::RenderFullScreenTexture(layer.texture);
    }
}