#ifndef POINT_H
#define POINT_H

#include <string>
#include <vector>

class Line;

class Point {
public:
	long double x;
	long double y;

	Point(long double x, long double y);
	bool operator<(const Point& another)const;

	long double getDistanceToLine(const Line& line);
};

namespace std {
    template <>
    struct hash<Point> {
        size_t operator()(Point const& p) const noexcept {
            return ((51 + std::hash<long double>()(p.x)) * 51 + std::hash<long double>()(p.y));
        }
    };

	inline bool operator == (const Point& p1, const Point& p2) {
		return p1.x == p2.x && p1.y == p2.y;
	}
}

#endif // !POINT_H
