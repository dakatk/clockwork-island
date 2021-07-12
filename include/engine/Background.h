#ifndef ENGINE_BACKGROUND_H__
#define ENGINE_BACKGROUND_H__

#include "engine/Texture.h"
#include <string>
#include <SDL.h>

#define BACKGROUND_NUM_LAYERS 3

namespace engine
{
    class Background
    {
    private:
        struct Layer
        {
            Texture *texture;

            int maxScrollX;
            int maxScrollY;
        };
        struct Layer layers[BACKGROUND_NUM_LAYERS]{};

    public:
        explicit Background(std::string filenames[BACKGROUND_NUM_LAYERS]);
        ~Background();

        void Scroll();
        void Render();
    };
}

#endif /* ENGINE_BACKGROUND_H__ */
