#include "AABB.h"
#include <algorithm>

AABB::AABB() : pos(Point(0, 0)), width(0), height(0)
{
}
AABB::AABB(const Point& point, int w, int h) : pos(point), width(w), height(h)
{
}
bool AABB::TestAABB(const AABB& box) const
{
    return !(pos.x + width < box.pos.x || box.pos.x + box.width < pos.x ||
        pos.y + height < box.pos.y || box.pos.y + box.height < pos.y);
}
bool AABB::TestPoint(const Point& q) const
{
    return (q.x >= pos.x && q.x <= pos.x + width &&
        q.y >= pos.y && q.y <= pos.y + height);
}
bool AABB::TestCircle(const Point& center, float radius) const
{
    int closest_x = std::max(pos.x, std::min(center.x, pos.x + width));
    int closest_y = std::max(pos.y, std::min(center.y, pos.y + height));
    int distance_x = center.x - closest_x;
    int distance_y = center.y - closest_y;
    return (distance_x * distance_x + distance_y * distance_y) <= (radius * radius);
}