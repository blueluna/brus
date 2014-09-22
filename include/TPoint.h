#ifndef TPOINT_H
#define TPOINT_H

class TPoint
{
public:
    TPoint();
    TPoint(float x, float y);

    void Set(float x, float y);

    bool operator == (const TPoint &other);

public:
    float Point[2];
};

#endif // TPOINT_H
