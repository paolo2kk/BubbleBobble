#pragma once
#include <cmath>
#include "Point.h"

class AABB {
public:
    Point pos;
    int width, height;

    AABB();
    AABB(const Point& point, int w, int h);

    bool TestAABB(const AABB& box) const;
    bool TestPoint(const Point& q) const;
    bool TestCircle(const Point& center, float radius) const;
};


