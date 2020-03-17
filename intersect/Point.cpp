#include "Point.h"
#include "Line.h"

float Point::esp = 1e-7f;

Point::Point(long double x, long double y) {
	this->x = ((int)round((float)(x + esp) * 1e6f)) / 1e6f;
	this->y = ((int)round((float)(y + esp) * 1e6f)) / 1e6f;
}

bool Point::operator<(const Point& another) const {
	if (MathUtil::d_equal(this->x, another.x) && MathUtil::d_equal(this->y, another.y)) {
		return false;
	}
	
	if (MathUtil::d_equal(this->x, another.x)) {
		return this->y < another.y;
	}
	return this->x < another.x;
}

long double Point::getDistanceToLine(const Line& line) {
	if (line.k == INT_MAX) {
		return abs(this->x - line.b);
	}

	long double molecule = abs(line.k * this->x + (-1) * (long double)this->y + line.b);
	long double denominator = sqrt(pow(line.k, 2) + 1);

	return molecule / denominator;
}
