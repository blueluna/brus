#ifndef TBOX_H
#define TBOX_H

#include "TPoint.h"

struct TBox
{
    float xmin;
    float ymin;
    float xmax;
    float ymax;

    TBox()
        : xmin(0.0f)
        , ymin(0.0f)
        , xmax(0.0f)
        , ymax(0.0f)
    {
    }

    float Width() const
    {
        return xmax - xmin;
    }

    float Height() const
    {
        return ymax - ymin;
    }

    TPoint Center() const
    {
        float xoffset = ((xmax - xmin) / 2.0f);
        float yoffset = ((ymax - ymin) / 2.0f);
        return TPoint(xmin + xoffset, ymin + yoffset);
    }

    void Grow(float delta)
    {
        xmin -= delta;
        xmax += delta;
        ymin -= delta;
        ymax += delta;
    }

    void Grow(float dx, float dy)
    {
        xmin -= dx;
        xmax += dx;
        ymin -= dy;
        ymax += dy;
    }

    void Move(float x, float y)
    {
        xmin += x;
        xmax += x;
        ymin += y;
        ymax += y;
    }
};

#endif // TBOX_H
