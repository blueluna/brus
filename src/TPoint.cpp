#include "TPoint.h"
#include <cstring>

TPoint::TPoint()
{
    memset(Point, 0, sizeof(float)*2);
}

TPoint::TPoint(float x, float y)
{
    Point[0] = x;
    Point[1] = y;
}

void TPoint::Set(float x, float y)
{
    Point[0] = x;
    Point[1] = y;
}

float TPoint::x() const
{
    return Point[0];
}

float TPoint::y() const
{
    return Point[1];
}

bool TPoint::operator == (const TPoint &other)
{
    return (Point[0] == other.Point[0]) && (Point[1] == other.Point[1]);
}
