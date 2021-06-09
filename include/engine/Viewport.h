#ifndef ENGINE_VIEWPORT_H__
#define ENGINE_VIEWPORT_H__

namespace engine
{
    class Viewport
    {
    private:
        static int x;
        static int y;

    public:
        static int GetX();
        static int GetY();

        static int GetMaxX();
        static int GetMaxY();

        static void Constrain();
        static void SnapTo(float centerX, float centerY);
    };
}

#endif /* ENGINE_VIEWPORT_H__ */
