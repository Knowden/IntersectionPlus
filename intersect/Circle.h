#ifndef CIRCLE_H
#define CIRCLE_H

#include <string>
#include <vector>

class Point;
class Line;

class Circle {
private:
	std::vector<Point> calculatePointsAtX(long double x);
	std::vector<Point> calculateIntersectionWithNormalLine(Line& line);

	void removeImpossiblePoints(std::vector<Point>& result, Line line);

	friend ostream& operator<<(ostream& out, Circle& circle);

public:
	Point* center;
	long double r;

	Circle(const std::string& input);
	Circle(long double x, long double y, long double r);


	std::vector<Point> getIntersectionWith(Line& line);
	std::vector<Point> getIntersectionWith(Circle& another);
};

#endif // !CIRCLE_H