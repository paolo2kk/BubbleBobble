#pragma once
#include <cmath>

class Point {
public:
    int x;
    int y;

    //Default constructor
    Point() : x(0), y(0) {}
    //Parameterized constructor
    Point(int px, int py) : x(px), y(py) {}
    //Copy constructor
    Point(const Point& p) : x(p.x), y(p.y) {}
    //Destructor
    ~Point() {}

    //Overloaded operators for arithmetic operations
    Point operator+(const Point& p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator-(const Point& p) const {
        return Point(x - p.x, y - p.y);
    }
    Point operator*(int scalar) const {
        return Point(x * scalar, y * scalar);
    }
    Point operator/(int divisor) const {
        //Ensure the divisor is not zero to avoid division by zero
        if (divisor != 0) {
            return Point(x / divisor, y / divisor);
        }
        //Handle division by zero gracefully (return a default point)
        return Point();
    }

    //Compound assignment operators
	Point& operator=(const Point& p) {
        x = p.x;
        y = p.y;
        return *this;
    }
    Point& operator+=(const Point& p) {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point& operator-=(const Point& p) {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point& operator*=(int scalar) {
        x *= scalar;
        y *= scalar;
        return *this;
    }
    Point& operator/=(int divisor) {
        //Ensure divisor is not zero to avoid division by zero
        if (divisor != 0) {
            x /= divisor;
            y /= divisor;
        }
        //Handle division by zero gracefully (no change)
        return *this;
    }
    bool operator!=(const Point& p) const {
        return (x != p.x) || (y != p.y);
    }

    //Distance method
    double distance(const Point& p) const {
        int dx = x - p.x;
        int dy = y - p.y;
        return std::sqrt(dx * dx + dy * dy);
    }
};