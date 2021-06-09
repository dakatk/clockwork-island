#ifndef CLOCKWORKISLAND_BOUNDINGBOX_H
#define CLOCKWORKISLAND_BOUNDINGBOX_H

namespace engine
{
    class BoundingBox
    {
    private:
        float centerX;
        float centerY;

        float halfWidth;
        float halfHeight;

    public:
        BoundingBox(float centerX, float centerY, float halfWidth, float halfHeight);

        float GetCenterX() const;
        float GetCenterY() const;

        void SetCenterX(float centerX);
        void SetCenterY(float centerY);

        float GetHalfWidth() const;
        float GetHalfHeight() const;

        float Top() const;
        float Left() const;
        float Right() const;
        float Bottom() const;

        void Move(float dx, float dy);

        bool Intersects(BoundingBox *other) const;
    };
}

#endif /* CLOCKWORKISLAND_BOUNDINGBOX_H */
