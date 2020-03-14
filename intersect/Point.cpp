#include "Point.h"
#include "Line.h"

Point::Point(long double x, long double y) {
	this->x = x;
	this->y = y;
}

bool Point::operator<(const Point& another) const {
	if (this->x == another.x && this->y == another.y) {
		return false;
	}
	
	if (this->x == another.x) {
		return this->y < another.y;
	}
	return this->x < another.x;
}

long double Point::getDistanceToLine(const Line& line) {
	if (line.k == INT_MAX) {
		return abs(this->x - line.b);
	}

	long double molecule = abs(line.k * this->x + (-1) * this->y + line.b);
	long double denominator = sqrt(pow(line.k, 2) + 1);

	return molecule / denominator;
}
